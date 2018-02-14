#include "curl/curl.h"
#include "curl/easy.h"
#include "feader.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xmlreader.h"
#include "libxml/xmlstring.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Please provide the URL of a feed to parse.\n");
        return 1;
    } else {
        printf("Attempting to retrieve XML for URL: %s\n", argv[1]);
    }

    fead_xml(argv[1]);

    return 0;
}

void fead_xml(char* url) {
    xml *x = malloc(sizeof(xml));
    get_xml_ptr(x, url);

    int res = get_xml(x);
    if (res == CURLE_OK) {
        printf("XML data retrieved from server\n");
    } else {
        printf("Unable to retrieve XML for URL: %s\n", x->url);
        printf("%s\n", x->errBuf);
    }

    parse_xml_items(x);

    save_xml_elements(x);

    cleanup_xml(x);
}

void get_xml_ptr(xml* x, char* url) {
    x->size = 0;
    x->data = malloc(1);
    x->data[0] = '\0';
    x->url = url;
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

size_t get_xml(xml* x) {
    CURL *curl = curl_easy_init();

    if (!curl) {
        printf("Unable to instantiate curl object. Aborting");
        return 1;
    } 

    curl_easy_setopt(curl, CURLOPT_URL, x->url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, *my_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, x);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, x->errBuf);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return res;
}

void parse_xml_items(xml *x) {
    xmlChar* xChar = xmlCharStrndup(x->data, x->size);
    x->xdp = xmlReadDoc(
            xChar,
            x->url,
            NULL,
            XML_PARSE_RECOVER
            );
    xmlFree(xChar);
}

void save_xml_elements(xml* x) {
    if (x->xdp == NULL || x->xdp->children == NULL) {
        printf("Unable to parse XML\n");
    }

    xmlNode* rss = x->xdp->children;
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
            xmlNode* itemData = channelChild->children;
            printf("Article info:\n");
            do {
                if (strncmp("text", itemData->name, strlen(itemData->name)) != 0) {
                    if (strlen(itemData->children->content) > 200) {
                        printf("%s: %ld chars\n", itemData->name, strlen(itemData->children->content));
                    } else {
                        printf("%s: %s\n", itemData->name, itemData->children->content);
                    }
                }
                itemData = itemData->next;
            } while (itemData != NULL);
            printf("\n");
        }
        channelChild = channelChild->next;
    }

    rss = NULL;
    channel = NULL;

    printf("Found %d articles in the feed\n", articleCount);    
}

void cleanup_xml(xml* x) { 
    free(x->data);
    free(x->errBuf);
    xmlFreeDoc(x->xdp);
    free(x);
}