#include "rendering/camera.h"
#include "rendering/math3d.h"
#include <math.h>

void camera_init(camera_t* camera, vec3_t position) {
    camera->position = position;
    camera->yaw = 0.0f;    // Looking straight ahead (along -Z axis)
    camera->pitch = 0.0f;  // Looking horizontally (not up or down)
}

void camera_rotate(camera_t* camera, float yaw_delta, float pitch_delta) {
    camera->yaw += yaw_delta;
    camera->pitch += pitch_delta;

    // Wrap yaw to 0-360 degrees
    if (camera->yaw > 360.0f) camera->yaw -= 360.0f;
    if (camera->yaw < 0.0f) camera->yaw += 360.0f;

    // Clamp pitch to prevent flipping upside down
    // -89 to +89 degrees
    if (camera->pitch > 89.0f) camera->pitch = 89.0f;
    if (camera->pitch < -89.0f) camera->pitch = -89.0f;
}

void camera_move_forward(camera_t* camera, float distance) {
    // Calculate forward direction based on yaw
    // In 3D space: forward is -Z when yaw = 0
    float yaw_rad = camera->yaw * (M_PI / 180.0f);

    // Move in the direction we're looking (ignoring pitch for movement)
    camera->position.x += sinf(yaw_rad) * distance;
    camera->position.z += cosf(yaw_rad) * distance;
}

void camera_move_right(camera_t* camera, float distance) {
    // Right is 90 degrees from forward
    float yaw_rad = (camera->yaw + 90.0f) * (M_PI / 180.0f);

    camera->position.x += sinf(yaw_rad) * distance;
    camera->position.z += cosf(yaw_rad) * distance;
}

void camera_move_up(camera_t* camera, float distance) {
    // Up is just positive Y
    camera->position.y += distance;
}