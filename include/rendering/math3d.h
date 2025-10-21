#ifndef TERMINATED_BY_C_MATH3D_H
#define TERMINATED_BY_C_MATH3D_H

#include "types.h"

vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
float vec3_length(vec3_t v);
vec3_t vec3_normalize(vec3_t v);

vec2_t project_to_screen(vec3_t world_point, camera_t* camera, int screen_width, int screen_height);

#endif //TERMINATED_BY_C_MATH3D_H