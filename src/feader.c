#include "curl/curl.h"
#include "curl/easy.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* data;
    int size;
} xml;

size_t my_write_callback(char *ptr, size_t size, size_t nmemb, xml *x);

size_t get_xml(xml *x, char *url);

int main(int argc, char **argv) {
    xml x;
    x.size = 0;
    x.data = malloc(1);
    x.data[0] = '\0';

    int res = get_xml(&x, "http://127.0.0.1/wbrawner-jekyll/_site/feed.xml");

    printf("\n%s\n", x.data);
    free(x.data);
    return res;
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
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}