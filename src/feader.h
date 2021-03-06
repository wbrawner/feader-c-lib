#include <libxml/tree.h>
#include <sqlite3.h>
#include <stdbool.h>
#define DB_FILE "feader.db"

typedef struct {
    char *data;
    int size;
    long totalSize;
    char *url;
    xmlDocPtr xdp;
} xml;

typedef struct {
    long id;
    char *title;
    char *url;
    long feed_id;
    char *author;
    bool is_favorite;
    char *featured_image;
    char *content;
    char *excerpt;
    bool is_read;
    char *published_date;
} article;

typedef struct {
    long id;
    char *title;
    char *site_url;
    char *feed_url;
    char *icon;
    bool is_favorite;
    char *last_polled;
    char *filter_accept;
    char *filter_reject;
} feed;

typedef struct {

} feed_with_articles;

size_t my_write_callback(char *ptr, size_t size, size_t nmemb, xml *x);

size_t get_xml(xml *x);

void parse_xml_items(xml *x);

void get_xml_ptr(xml* x, char* url);

void print_xml_elements(xml* x);

void save_xml_elements(xml* x);

void cleanup_xml(xml* x);

void fead_xml(char* url);

void setup_database(sqlite3* handle);

void close_database(sqlite3* handle);

