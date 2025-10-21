#ifndef TERMINATED_BY_C_CAMERA_H
#define TERMINATED_BY_C_CAMERA_H

#include "types.h"

struct camera {
    vec3_t position;
    float yaw;
    float pitch;
};

void camera_init(camera_t* camera, vec3_t position);
void camera_rotate(camera_t* camera, float yaw_delta, float pitch_delta);
void camera_move_forward(camera_t* camera, float distance);
void camera_move_right(camera_t* camera, float distance);
void camera_move_up(camera_t* camera, float distance);

#endif //TERMINATED_BY_C_CAMERA_H