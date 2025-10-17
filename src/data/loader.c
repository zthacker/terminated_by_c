

#include <stdio.h>
#include "../include/data/loader.h"

#include <stdlib.h>

character_t* load_character_from_json(const char* file_path) {
    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // make buffer
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        perror("Error allocating memory");
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // null terminate
    fclose(file);

    // parse json
    cJSON* json_string = cJSON_Parse(buffer);
    if (json_string == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        return NULL;
    }

    // free buffer
    free(buffer);

    // access JSON
    cJSON* name = cJSON_GetObjectItemCaseSensitive(json_string, "name");
    cJSON* level = cJSON_GetObjectItemCaseSensitive(json_string, "level");

    if (!cJSON_IsString(name) || !cJSON_IsNumber(level)) {
        fprintf(stderr, "Error: JSON is missing 'name' (string) or 'level' (number).\n");
        cJSON_Delete(json_string);
        return NULL;
    }

    character_t* character = character_create(name->valuestring, level->valueint);
    cJSON_Delete(json_string);


    return character;
}
