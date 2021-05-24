#include "my_curl.h"

static size_t cb(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)
        return 0;  /* out of memory! */
 
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
    
    return realsize;
}

char* make_request(const char* url_string)
{
  CURL *curl;

  struct memory chunk = {NULL, 0};

  curl = curl_easy_init(); 
  if (curl){
    curl_easy_setopt(curl, CURLOPT_URL, url_string);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK){
        curl_easy_cleanup(curl);
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return NULL;
    }
    curl_easy_cleanup(curl);
    return chunk.response;
  }
  
  return NULL;
}

char* make_url_string(const char* str1,const char* str2,const char* str3)
{
  size_t urlstrlen = strlen(str1) + strlen(str2) + strlen(str3);
  char *url_string = (char* )malloc(sizeof(char) * urlstrlen);
  if (url_string == NULL){
    perror("malloc:");
    return NULL;
  }

  snprintf(url_string, urlstrlen, "%s%s%s", str1, str2, str3);
  return url_string;
}