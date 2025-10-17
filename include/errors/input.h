
#ifndef TERMINATED_BY_C_INPUT_H
#define TERMINATED_BY_C_INPUT_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static inline bool check_input_error(char* endPtr, char* input) {
    if (!endPtr) {
        return false;
    }

    if (endPtr == input) {
        fprintf(stderr, "No number found in %s.\n", input);
        return false;
    }

    if (*endPtr != '\0') {
        fprintf(stderr, "Error: Invalid character in %s after number : %s", endPtr, input);
        return false;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Error: Number %s out of range for long int\n", input);
        return false;
    }

    return true;
}

#endif //TERMINATED_BY_C_INPUT_H