#include "curl/curl.h"
#include "/usr/local/include/curl/easy.h"
#include <stdio.h>

size_t my_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

int main(int argc, char** argv) {
    CURL *curl = curl_easy_init();

    if (!curl) {
        printf("Unable to instantiate curl object. Aborting");
        return 1;
    }

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/wbrawner-jekyll/_site/feed.xml");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, *my_write_callback);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

size_t my_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("Got the following from the server: \n%s\n", ptr);
    return 0;
}
