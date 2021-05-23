#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_curl.h"
#include "my_json.h"

int make_request();


int main(int argc, char* argv[])
{
  if (argc < 2){
    printf("Usage: ./weather.out cityname\n");
    return EXIT_FAILURE;
  }

  CURL *curl;
  struct memory chunk;

  chunk.response = malloc(1);
  chunk.size = 0;  

  curl = curl_easy_init();
  if(curl) {

    /*Get woeid*/
    size_t urlstrlen = sizeof(URL_WOEID_STRING) + sizeof(argv[1]) + 1;
    char *url_string = (char* )malloc(sizeof(char) * urlstrlen);
    snprintf(url_string, urlstrlen, "%s%s", URL_WOEID_STRING, argv[1]);

    /*Make url request woeid*/
    if (!(curl_get(curl, url_string, &chunk))){
      curl_easy_cleanup(curl);
      free(url_string);
      return EXIT_FAILURE;
    }
    free(url_string);

    /*Parse json string woeid*/
    char woeid[WOEID_SIZE] = {0};
    if (!(json_field_get(chunk.response, "woeid", woeid))){
      curl_easy_cleanup(curl);
      return EXIT_FAILURE;
    }

    /*Get weather*/
    urlstrlen = sizeof(URL_WEATH_STRING) + sizeof(woeid) + 14;
    url_string = (char* )malloc(sizeof(char) * urlstrlen);
    snprintf(url_string, urlstrlen, "%s%s%s", URL_WEATH_STRING, woeid, "/2021/05/21/");

    /*Make url request weather*/
    if (!(curl_get(curl, url_string, &chunk))){
      curl_easy_cleanup(curl);
      free(url_string);
      return EXIT_FAILURE;
    }
    free(url_string); 
  
    /*Parse json string woeid*/
    char weather[WEATH_SIZE] = {0};
    if (!(json_field_get(chunk.response, "title", weather))){
      curl_easy_cleanup(curl);
      return EXIT_FAILURE;
    }

    printf("%s\n", weather);
    curl_easy_cleanup(curl);
  }
  return 0;
}
