#include "curl/curl.h"
#include "curl/easy.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xmlreader.h"
#include "libxml/xmlstring.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* data;
    int size;
    char* url;
    char* errBuf;
} xml;

size_t my_write_callback(char *ptr, size_t size, size_t nmemb, xml *x);

size_t get_xml(xml *x, char *url);

void parse_xml_items(xml *x, xmlDocPtr *doc);

xml x;

xmlDocPtr xdp;

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Please provide the URL of a feed to parse.\n");
        return 1;
    } else {
        printf("Attempting to retrieve XML for URL: %s\n", argv[1]);
    }
    x.size = 0;
    x.data = malloc(1);
    x.data[0] = '\0';
    x.url = argv[1];

    int res = get_xml(&x, x.url);
    // printf("\n%s\n", x.data);            
    if (res == CURLE_OK) {
        printf("XML data retrieved from server\n");
    } else {
        printf("Unable to retrieve XML for URL: %s\n", x.url);
        printf("%s\n", x.errBuf);
    }

    parse_xml_items(&x, &xdp);

    if (xdp == NULL || xdp->children == NULL) {
        printf("Unable to parse XML\n");
    }

    xmlNode* rss = xdp->children;
    xmlNode* channel = rss->children->next;
    xmlNode* channelChild = channel->children;
    int articleCount = 0;
    while (channelChild != NULL) {
        if (strncmp("title", channelChild->name, strlen(channelChild->name)) == 0) {
            if (channelChild->children != NULL) {
                printf("%s: %s\n", channelChild->name, channelChild->children->content);
            }
        } else if (strncmp("description", channelChild->name, strlen(channelChild->name)) == 0) {
            if (channelChild->children != NULL) {
                printf("%s: %s\n", channelChild->name, channelChild->children->content);
            }
        } else if (strncmp("item", channelChild->name, strlen(channelChild->name)) == 0) {
            articleCount++;
        }
        channelChild = channelChild->next;
    }

    printf("Found %d articles in the feed\n", articleCount);


    free(x.data);
    free(xdp);
    return 0;
}

size_t my_write_callback(char *ptr, size_t size, size_t nmemb, xml *x) {
    int byte_size = (size * nmemb);
    printf("byte_size: %d\n", byte_size);
    int new_size = x->size + byte_size;
    printf("new_size size: %d\n", new_size);
    x->data = realloc(x->data, new_size + 1);
    memcpy(x->data + x->size, ptr, byte_size);
    x->data[new_size] = '\0';
    x->size = new_size;
    printf("New xml size: %d\n", x->size);
    return byte_size;
}

size_t get_xml(xml* x, char* url) {
    CURL *curl = curl_easy_init();   

    if (!curl) {
        printf("Unable to instantiate curl object. Aborting");
        return 1;
    } 
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, *my_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, x);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, x->errBuf);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

void parse_xml_items(xml *x, xmlDocPtr *doc) {
    xmlChar* xChar = malloc(x->size);
    xChar = xmlCharStrndup(x->data, x->size);
    (*doc) = xmlReadDoc(
            xChar,
            x->url,
            NULL,
            XML_PARSE_RECOVER
            );
    free(xChar);
}
