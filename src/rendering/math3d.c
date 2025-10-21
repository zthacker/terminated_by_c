#include "rendering/math3d.h"
#include "rendering/camera.h"
#include <math.h>

// =============================================================================
// Vector Math Functions
// =============================================================================

vec3_t vec3_add(vec3_t a, vec3_t b) {
    vec3_t result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
    vec3_t result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

float vec3_length(vec3_t v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3_normalize(vec3_t v) {
    float len = vec3_length(v);
    vec3_t result;

    if (len > 0.0f) {
        result.x = v.x / len;
        result.y = v.y / len;
        result.z = v.z / len;
    } else {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
    }
    return result;
}

// =============================================================================
// Functions
// =============================================================================

vec2_t project_to_screen(vec3_t world_point, camera_t* camera, int screen_width, int screen_height) {

    // world point to camera space
    vec3_t relative = vec3_sub(world_point, camera->position);

    // apply rotation
    float yaw_rad = camera->yaw * (M_PI / 180.0f);
    float pitch_rad = camera->pitch * (M_PI / 180.0f);

    float cos_yaw = cosf(yaw_rad);
    float sin_yaw = sinf(yaw_rad);
    float cos_pitch = cosf(pitch_rad);
    float sin_pitch = sinf(pitch_rad);

    // rotate around X axis (pitch) - looking up and down
    float y_temp = relative.y * cos_pitch + relative.z * sin_pitch;
    float z_temp = -relative.y * sin_pitch + relative.z * cos_pitch;
    relative.y = y_temp;
    relative.z = z_temp;

    // perspective projection
    vec2_t screen_pos;

    // focal -- higher = zoomed in; lower == zoomed out
    float focal_length = 500.0f;

    // avoid divide by 0
    if (relative.z <= 0.1f) {
        screen_pos.x = -1000.0; // off screen marker
        screen_pos.y = 1000.0;
        return screen_pos;
    }

    // make distant objects appear smaller
    screen_pos.x = (relative.x / relative.z) * focal_length + (screen_width / 2.0f);
    screen_pos.y = -(relative.y / relative.z) * focal_length + (screen_height / 2.0f); // negative y b/c screen coords go down, but 3D y goes up

    return screen_pos;

}
