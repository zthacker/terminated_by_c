#include "../../include/character/character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Privates ---


// --- Publics ---

character_t* character_create(char* name, int level)
{
    if (name == NULL || level < 0) return NULL;

    character_t* character = (character_t*)malloc(sizeof(character_t));
    if (!character)
        return NULL;

    //copy and take control of the memory for name and null termination
    snprintf(character->name, CHARACTER_NAME_LENGTH_MAX, "%s", name);

    character->level = level;
    return character;
}

void character_destroy(character_t* character)
{
    if (character) {
        free(character);
        character = NULL;

    }
}

bool character_update_name(character_t* character, char* name)
{
    if (!character || !name)
        return false;

    snprintf(character->name, CHARACTER_NAME_LENGTH_MAX, "%s", name);

    return true;
}
