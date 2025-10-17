#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data/loader.h"
#include "include/character/character.h"
#include "include/errors/input.h"
#include "include/utils/file_path.h"



int main(int argc, char* argv[]) {

    // path to exe
    printf("Executable path is: %s\n", argv[0]);

    // abs path to asset
    const char* character_path = get_path_relative_to_exe(argv[0], "character.json");
    if (!character_path) {
        printf("Failed to get character path\n");
        return EXIT_FAILURE;
    }

    // game loop!
    char input[INPUT_BUFFER_SIZE];
    int running = 1;

    character_t* character = character_create("", 1);

    while (running) {
        printf("\nWelcome, prepate to be C Terminated\n");
        printf("1. New Character\n");
        printf("2. Load Character\n");
        printf("3. Update Character\n");
        printf("4. Quit\n");
        printf("> ");

        // read user input -- fgets returns NULL if there was an error
        if (fgets(input, INPUT_BUFFER_SIZE, stdin) == NULL) {
            break; // EOF or error
        }

        // remove newline characters
        input[strcspn(input, "\n")] = '\0';



        // parse the input
        if (strcmp(input, "1") == 0) {
            printf("Enter your Character's Name: ");
            char name[CHARACTER_NAME_LENGTH_MAX];
            fgets(name, CHARACTER_NAME_LENGTH_MAX, stdin);
            name[strcspn(name, "\n")] = '\0';
            if (!character_update_name(character, name)) {
                running = 0;
            } else {
                printf("Character Created: %s : %d\n", name, 1);
            }
        }
        else if (strcmp(input, "2") == 0) {
            character_t* new_character = load_character_from_json(character_path);
            if (!new_character) {
                printf("Character Load Failed\n");
                running = 0;
            } else {
                memcpy(character, new_character, sizeof(character_t));
                printf("Character Loaded: %s : %d\n", character->name, character->level);
                free(new_character);
            }
        }
        else if (strcmp(input, "3") == 0) {
            printf("Enter your Character's New Name: ");
            char name[CHARACTER_NAME_LENGTH_MAX];
            fgets(name, CHARACTER_NAME_LENGTH_MAX, stdin);
            name[strcspn(name, "\n")] = '\0';
            if (!character_update_name(character, name)) {
                running = 0;
            } else {
                printf("Character Name Updated: %s : %d\n", name, 1);
            }
        }
        else if (strcmp(input, "4") == 0) {
            printf("Ok, BYE!\n");
            running = 0;
        }
        else {
            printf("Incorrect input!\n");
        }
    }

    character_destroy(character);
    return EXIT_SUCCESS;
}
