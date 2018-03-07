#include "feader.h"
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Please provide the URL of a feed to parse.\n");
        return 1;
    } else {
        printf("Attempting to retrieve XML for URL: %s\n", argv[1]);
    }
    
    sqlite3 *db;
    setup_database(db);

    fead_xml(argv[1]);

    close_database(db);

    return 0;
}

void fead_xml(char* url) {
    xml *x = malloc(sizeof(xml));
    get_xml_ptr(x, url);

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

void parse_xml_items(xml *x) {
//     xmlChar* xChar = xmlCharStrndup(x->data, x->size);
//     x->xdp = xmlReadDoc(
//             xChar,
//             x->url,
//             NULL,
//             XML_PARSE_RECOVER
//             );
//     xmlFree(xChar);
}

void print_xml_elements(xml* x) {
//     if (x->xdp == NULL || x->xdp->children == NULL) {
//         printf("Unable to parse XML\n");
//     }

//     xmlNode* rss = x->xdp->children;
//     xmlNode* channel = rss->children->next;
//     xmlNode* channelChild = channel->children;
//     int articleCount = 0;
//     while (channelChild != NULL) {
//         if (strncmp("title", channelChild->name, strlen(channelChild->name)) == 0) {
//             if (channelChild->children != NULL) {
//                 printf("%s: %s\n", channelChild->name, channelChild->children->content);
//             }
//         } else if (strncmp("description", channelChild->name, strlen(channelChild->name)) == 0) {
//             if (channelChild->children != NULL) {
//                 printf("%s: %s\n", channelChild->name, channelChild->children->content);
//             }
//         } else if (strncmp("item", channelChild->name, strlen(channelChild->name)) == 0) {
//             articleCount++;
//             xmlNode* itemData = channelChild->children;
//             printf("Article info:\n");
//             do {
//                 if (strncmp("text", itemData->name, strlen(itemData->name)) != 0) {
//                     if (strlen(itemData->children->content) > 200) {
//                         printf("%s: %ld chars\n", itemData->name, strlen(itemData->children->content));
//                     } else {
//                         printf("%s: %s\n", itemData->name, itemData->children->content);
//                     }
//                 }
//                 itemData = itemData->next;
//             } while (itemData != NULL);
//             printf("\n");
//         }
//         channelChild = channelChild->next;
//     }

//     rss = NULL;
//     channel = NULL;

//     printf("Found %d articles in the feed\n", articleCount);    
}

void cleanup_xml(xml* x) { 
    free(x->data);
    free(x->errBuf);
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

void close_database(sqlite3* handle) {
    sqlite3_close(handle);
}
