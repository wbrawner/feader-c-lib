#include "feader.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xmlreader.h>
#include <libxml2/libxml/xmlstring.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please provide the URL of a feed to parse.\n");
        return 1;
    } else {
        printf("Attempting to retrieve XML for URL: %s\n", argv[1]);
    }

    sqlite3* db;
    setup_database(db);
    fead_xml(argv[1]);
    close_database(db);
    return 0;
}

void fead_xml(char* url) {
    xml* x = malloc(sizeof(xml));
    get_xml_ptr(x, url);

    int res = get_xml(x);
    if (res == CURLE_OK) {
        printf("XML data retrieved from server\n");
    } else {
        printf("Unable to retrieve XML for URL: %s\n", x->url);
    }
    parse_xml_items(x);
    print_xml_elements(x);
    cleanup_xml(x);
}

void get_xml_ptr(xml* x, char* url) {
    x->size = 0;
    x->data = malloc(1);
    x->data[0] = '\0';
    x->url = url;
}

size_t my_write_callback(char* ptr, size_t size, size_t nmemb, xml* x) {
    int byte_size = (size * nmemb);
    int new_size = x->size + byte_size;
    x->data = realloc(x->data, new_size + 1);
    memcpy(x->data + x->size, ptr, byte_size);
    x->data[new_size] = '\0';
    x->size = new_size;
    return byte_size;
}

size_t get_xml(xml* x) {
    CURL* curl = curl_easy_init();

    if (!curl) {
        printf("Unable to instantiate curl object. Aborting");
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, x->url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, x);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return res;
}

void parse_xml_items(xml* x) {
    xmlChar* xChar = xmlCharStrndup(x->data, x->size);
    x->xdp = xmlReadDoc(xChar, x->url, NULL, XML_PARSE_RECOVER);
    xmlFree(xChar);
}

void parse_entry(xmlNode *root) {

}

article * parse_item(xmlNode *item) {
    printf("Article info:\n");
    do {
        if (strncmp("text", item->name, strlen(item->name)) != 0) {
            if (strlen(item->children->content) > 200) {
                printf("%s: %ld chars\n", item->name,
                        strlen(item->children->content));
            } else {
                printf("%s: %s\n", item->name, item->children->content);
            }
        }
        item = item->next;
    } while (item != NULL);
    printf("\n");
    return NULL;
}

feed * parse_feed(xmlNode *feed) {
    while (feed && strcmp(feed->name, "entry") != 0) {
        feed = feed->next;
    }

}

feed * parse_rss(xmlNode *rss) {
    xmlNode* channel = rss->children->next;
    xmlNode* channelChild;
    while (channel && strcmp(channel->name, "channel") != 0) {
        channel = channel->next;
    }
    while (channelChild != NULL) {
        if (strncmp("title", channelChild->name, strlen(channelChild->name) - 1) == 0) {
            if (channelChild->children != NULL) {
                printf("%s: %s\n", channelChild->name, channelChild->children->content);
            }
        } else if (strncmp("description", channelChild->name,
                    strlen(channelChild->name)) == 0) {
            if (channelChild->children != NULL) {
                printf("%s: %s\n", channelChild->name, channelChild->children->content);
            }
        } else if (strncmp("item", channelChild->name,
                    strlen(channelChild->name)) == 0) {
            article *article = parse_item(channelChild->children);
            // TODO: Store articles in array to return
        }
        channelChild = channelChild->next;
    }
}

void print_xml_elements(xml* x) {
    if (x->xdp == NULL || x->xdp->children == NULL) {
        printf("Unable to parse XML\n");
    }

    xmlNode* root = x->xdp->children;
    if (strcmp(root->name, "rss") == 0) {
        parse_rss(root);
    } else if (strcmp(root->name, "feed") == 0){
        parse_feed(root);
    } else {
        printf("Unable to parse XML\n");
        // TODO: Return error
        return;
    }

    int articleCount = 0;

    root = NULL;
    printf("Found %d articles in the feed\n", articleCount);
}

void cleanup_xml(xml* x) {
    if (!x) return;
    if (x->data) free(x->data);
    if (x->xdp) xmlFreeDoc(x->xdp);
    free(x);
}

void setup_database(sqlite3* handle) {
    char* init_sql =
#include "schema.sql"
        ;
    char* err;

    sqlite3_open(DB_FILE, &handle);
    sqlite3_exec(handle, init_sql, NULL, NULL, &err);
    if (err != NULL) {
        printf("Error setting up databases: %s\n", err);
    }
}

void close_database(sqlite3* handle) { sqlite3_close(handle); }
