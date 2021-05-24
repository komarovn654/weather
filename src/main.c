#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "my_curl.h"
#include "my_json.h"

void reverse(char s[])
{
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)
        n =-n;          
    i = 0;
    do { 
        s[i++] = n % 10 + '0';  
    } while ((n /= 10) > 0);  
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void date_get(char *date)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
  
    char cd[14] = {0};
    char year[5] = {0}, month[3] = {0}, day[3] = {0};
    itoa(tm.tm_year + 1900, year);
    itoa(tm.tm_mon + 1, month);
    itoa(tm.tm_mday, day);
    snprintf(cd, 14, "/%s/%s/%s//", year, month, day);
    strcpy(date, cd);
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        printf("Usage: ./weather.out cityname\n");
        return EXIT_FAILURE;
    }

    /*Make woeid request*/
    char *url_string = {0};
    if ((url_string = make_url_string(URL_WOEID_STRING, argv[1], " ")) == NULL)
        return EXIT_FAILURE;
    
    char *response = {0};
    if ((response = make_request(url_string)) == NULL){
        free(url_string);
        return EXIT_FAILURE;
    }

    char woeid[WOEID_SIZE] = {0};
    char city[CITY_SIZE] = {0};
    if (json_field_get(response, "woeid", woeid) == 0){
        free(url_string);
        free(response);
        return EXIT_FAILURE;
    }
    json_field_get(response, "title", city);
    printf("City: %s\n", city);
    free(url_string);
    free(response);

    /*Make weather request*/
    char date[20] = {0};
    date_get(date);
    if ((url_string = make_url_string(URL_WEATH_STRING, woeid, date)) == NULL)
        return EXIT_FAILURE;
  
    if ((response = make_request(url_string)) == NULL){
        free(url_string);
        return EXIT_FAILURE;
    }
  
    char weather[WEATH_SIZE] = {0};
    for (size_t i = 0; i < NUM_PARAMETERS; ++i){
        switch (i){
            case created:
                json_field_get(response, "created", weather);     
                printf("Date of report creation: %s\n", weather);
                break;
            case weather_state_name:
                json_field_get(response, "weather_state_name", weather);     
                printf("Weather state: %s\n", weather);
                break;    
            case the_temp:
                json_field_get(response, "the_temp", weather);     
                printf("Temperature: %s\n", weather);
                break;
            case wind_speed:
                json_field_get(response, "wind_speed", weather);     
                printf("Wind speed: %s\n", weather);
                break;
            case air_pressure:
                json_field_get(response, "air_pressure", weather);     
                printf("Air pressure: %s\n", weather);
                break;  
            case humidity:
                json_field_get(response, "humidity", weather);     
                printf("Humidity: %s\n", weather);
                break; 
            case visibility:
                json_field_get(response, "visibility", weather);     
                printf("Visibility: %s\n", weather);
                break;                                              
            default:
            break;
        }
    }

    free(url_string);
    free(response);
    return 0;
}
