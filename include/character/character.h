#ifndef TERMINATED_BY_C_CHARACTER_H
#define TERMINATED_BY_C_CHARACTER_H
#include <stdbool.h>
#include "../types.h"

typedef struct character {
    char name[CHARACTER_NAME_LENGTH_MAX];
    int level;
} character_t;

character_t* character_create(char* name, int level);
void character_destroy(character_t* character);
bool character_update_name(character_t* character, char* name);


#endif //TERMINATED_BY_C_CHARACTER_H