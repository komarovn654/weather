#ifndef MY_JSON_H
#define MY_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define WOEID_SIZE 256
#define WEATH_SIZE 256
#define CITY_SIZE 256

enum wp
{
    created, 
    weather_state_name,
    the_temp,
    wind_speed,
    air_pressure,
    humidity,
    visibility,
    NUM_PARAMETERS
};

int json_field_get(const char* json_string, const char *key, char *field);

#endif