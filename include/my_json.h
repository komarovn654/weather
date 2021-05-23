#ifndef MY_JSON_H
#define MY_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define WOEID_SIZE 256
#define WEATH_SIZE 256

int json_field_get(const char* json_string, const char *key, char *field);

#endif