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

//static size_t cb(void *data, size_t size, size_t nmemb, void *userp);
int curl_get(CURL *curl_handle, const char* url, struct memory *data);

#endif