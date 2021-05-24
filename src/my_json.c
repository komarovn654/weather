#include "my_json.h"

int json_field_get(const char* json_string, const char *key, char *field)
{
    json_object *new_object = json_tokener_parse(json_string);
    json_object *tmp, *array_index;

    if (json_object_get_type(new_object) != json_type_array){
        printf("Json string format error, expected json_type_array\n");
        return 0;
    }
  
    size_t arraylen = json_object_array_length(new_object);
    for (size_t i = 0; i < arraylen; ++i){
        array_index = json_object_array_get_idx(new_object, i);
        if (json_object_object_get_ex(array_index, key, &tmp) != 0)
        break;
        printf("The key \"%s\" was not found\n", key);
        json_object_put(new_object);
        return 0;
    }

    const char *foo = json_object_to_json_string(tmp);
    strcpy(field, foo);

	json_object_put(new_object);

    return 1;
}