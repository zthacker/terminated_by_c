#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data/loader.h"
#include "include/character/character.h"
#include "include/errors/input.h"
#include "include/utils/file_path.h"
#include <SDL3/SDL.h>

#include "rendering/camera.h"
#include "rendering/math3d.h"


int main(int argc, char* argv[]) {

    // init SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }



    // path to exe
    printf("Executable path is: %s\n", argv[0]);

    // abs path to asset
    const char* character_path = get_path_relative_to_exe(argv[0], "character.json");
    if (!character_path) {
        printf("Failed to get character path\n");
        return EXIT_FAILURE;
    }

    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!SDL_CreateWindowAndRenderer("Terminated by C", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // camera
    camera_t camera;
    vec3_t cam_pos = {0.0f, 0.0f, -5.0f};
    camera_init(&camera, cam_pos);

    //3d cube
    vec3_t cube_points[8] = {
        {-1, -1, -1},  // 0: bottom-left-back
        { 1, -1, -1},  // 1: bottom-right-back
        { 1,  1, -1},  // 2: top-right-back
        {-1,  1, -1},  // 3: top-left-back
        {-1, -1,  1},  // 4: bottom-left-front
        { 1, -1,  1},  // 5: bottom-right-front
        { 1,  1,  1},  // 6: top-right-front
        {-1,  1,  1}   // 7: top-left-front
    };

    // game loop!
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                    break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    running = false;
                }
                break;
            case SDL_EVENT_MOUSE_MOTION:
                // rotate cam based on mouse movement
                camera_rotate(&camera, event.motion.xrel * 0.2f,
                                      -event.motion.yrel * 0.2f);
                break;
            }
        }

        // update logic
        // get keys
        const bool* keys = SDL_GetKeyboardState(NULL);
        float move_speed = 0.05f;

        // forward back
        if (keys[SDL_SCANCODE_W]) camera_move_forward(&camera, move_speed);
        if (keys[SDL_SCANCODE_S]) camera_move_forward(&camera, -move_speed);

        // left right
        if (keys[SDL_SCANCODE_A]) camera_move_right(&camera, -move_speed);
        if (keys[SDL_SCANCODE_D]) camera_move_right(&camera, move_speed);

        // up down
        if (keys[SDL_SCANCODE_SPACE]) camera_move_up(&camera, move_speed);
        if (keys[SDL_SCANCODE_LSHIFT]) camera_move_up(&camera, -move_speed);

        // clear screen
        SDL_SetRenderDrawColor(renderer, 20, 30, 50, 255);
        SDL_RenderClear(renderer);

        // draw stuff
        int w, h;
        SDL_GetWindowSize(window, &w, &h);

        // draw cube
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        for (int i = 0; i < 8; i++) {
            // Project each 3D point to 2D screen space
            vec2_t screen_pos = project_to_screen(cube_points[i], &camera, w, h);

            // Only draw if point is in front of camera
            if (screen_pos.x >= 0 && screen_pos.x < w &&
                screen_pos.y >= 0 && screen_pos.y < h) {
                // Draw a small circle for each point
                for (int dx = -3; dx <= 3; dx++) {
                    for (int dy = -3; dy <= 3; dy++) {
                        if (dx*dx + dy*dy <= 9) { // Circle radius ~3
                            SDL_RenderPoint(renderer,
                                          screen_pos.x + dx,
                                          screen_pos.y + dy);
                        }
                    }
                }
                }
        }

        // Draw crosshair
        float cx = w / 2.0f;
        float cy = h / 2.0f;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderLine(renderer, cx - 10, cy, cx + 10, cy);
        SDL_RenderLine(renderer, cx, cy - 10, cx, cy + 10);

        SDL_RenderPresent(renderer);
        SDL_DelayNS(16666666); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
