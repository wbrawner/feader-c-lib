#include "sqlite/sqlite3.h"
#define DB_FILE "feader.db"

typedef struct {
    char* data;
    int size;
    long totalSize;
    char* url;
    char* errBuf;
} xml;

void parse_xml_items(xml *x);

void get_xml_ptr(xml* x, char* url);

void print_xml_elements(xml* x);

void save_xml_elements(xml* x);

void cleanup_xml(xml* x);

void fead_xml(char* url);

void setup_database(sqlite3* handle);

void close_database(sqlite3* handle);
