#ifndef MY_CURL_H
#define MY_CURL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define URL_WOEID_STRING "https://www.metaweather.com/api/location/search/?query="
#define URL_WEATH_STRING "https://www.metaweather.com/api/location/"

struct memory {
    char *response;
    size_t size;
};

char* make_request(const char* url_string);
char* make_url_string(const char* str1,const char* str2,const char* str3);
#endif