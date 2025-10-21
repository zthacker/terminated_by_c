//
// Created by User on 10/11/2025.
//

#ifndef TERMINATED_BY_C_TYPES_H
#define TERMINATED_BY_C_TYPES_H

#define CHARACTER_NAME_LENGTH_MAX 16
#define INPUT_BUFFER_SIZE 1024
#include <stdint.h>


// =============================================================================
// Common Math Types
// =============================================================================

typedef struct vec2 {
    float x, y;
} vec2_t;

typedef struct vec3 {
    float x, y, z;
} vec3_t;

typedef struct vec4 {
    float x, y, z, w;
} vec4_t;

// Integer versions
typedef struct vec2i {
    int x, y;
} vec2i_t;

typedef struct vec3i {
    int x, y, z;
} vec3i_t;

// =============================================================================
// Common Game Types
// =============================================================================

typedef struct dimensions {
    int width;
    int height;
} dimensions_t;

typedef struct color {
    uint8_t r, g, b, a;
} color_t;

// =============================================================================
// Forward Declarations (to avoid circular dependencies)
// =============================================================================

typedef struct camera camera_t;


#endif //TERMINATED_BY_C_TYPES_H