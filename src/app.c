// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/app.h"
#include "../include/image.h"

static void fail(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

static void load_current(app *a) {
    if (a->texture) SDL_DestroyTexture(a->texture);

    a->texture = image_load(
        a->renderer,
        a->files[a->file_index],
        &a->img_w,
        &a->img_h
    );

    int win_w, win_h;
    SDL_GetWindowSize(a->window, &win_w, &win_h);

    int iw = a->img_w;
    int ih = a->img_h;

    if (((int)a->rotation % 180) != 0) {
       int tmp = iw;
       iw = ih;
       ih = tmp;
    }

    float zoom_x = (float)win_w / iw;
    float zoom_y = (float)win_h / ih;

    a->zoom = (zoom_x < zoom_y) ? zoom_x : zoom_y;

    a->offset_x = 0;
    a->offset_y = 0;
    a->rotation = 0.0;
    a->flip = SDL_FLIP_NONE;
}

static void draw(app *a) {
    int win_w, win_h;
    SDL_GetWindowSize(a->window, &win_w, &win_h);

    SDL_Rect dst;
    dst.w = (int)(a->img_w * a->zoom);
    dst.h = (int)(a->img_h * a->zoom);
    dst.x = win_w / 2 - dst.w / 2 + (int)a->offset_x;
    dst.y = win_h / 2 - dst.h / 2 + (int)a->offset_y;

    SDL_RenderClear(a->renderer);
    SDL_RenderCopyEx(
    a->renderer,
    a->texture,
    NULL,
    &dst,
    a->rotation,
    NULL,
    a->flip
    );
    SDL_RenderPresent(a->renderer);
}

void app_init(app *a, char **files, int count) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) fail(SDL_GetError());
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP | IMG_INIT_TIF)))
        fail(IMG_GetError());

    a->files = files;
    a->file_count = count;
    a->file_index = 0;
    a->texture = NULL;
    a->rotation = 0.0;
    a->flip = SDL_FLIP_NONE;
    a->dragging = 0;

    a->window = SDL_CreateWindow(
        "Iris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        900,
        700,
        SDL_WINDOW_RESIZABLE
    );
    if (!a->window) fail(SDL_GetError());

    a->renderer = SDL_CreateRenderer(
        a->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!a->renderer) fail(SDL_GetError());

    SDL_SetRenderDrawColor(a->renderer, 0, 0, 0, 255);

    load_current(a);
}

void app_run(app *a) {
    int run = 1;
    while (run) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) run = 0;
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
               load_current(a);
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        run = 0;
                        break;

                    case SDLK_RIGHT:
                        a->file_index = (a->file_index + 1) % a->file_count;
                        load_current(a);
                        break;

                    case SDLK_LEFT:
                        a->file_index = (a->file_index - 1 + a->file_count) % a->file_count;
                        load_current(a);
                        break;

                    case SDLK_PLUS:
                    case SDLK_KP_PLUS:
                    case SDLK_EQUALS:
                        a->zoom *= 1.1f;
                        break;

                    case SDLK_MINUS:
                    case SDLK_KP_MINUS:
                        a->zoom *= 0.9f;
                        break;

                    case SDLK_q:
                        a->rotation -= 90.0;
                        if (a->rotation < 0) a->rotation += 360.0;
                        break;

                    case SDLK_e:
                        a->rotation += 90.0;
                        if (a->rotation >= 360.0) a->rotation -= 360.0;
                        break;

                    case SDLK_h:
                        a->flip ^= SDL_FLIP_HORIZONTAL;
                        break;

                    case SDLK_v:
                        a->flip ^= SDL_FLIP_VERTICAL;
                        break;

                    case SDLK_r:
                        load_current(a);
                        break;

                }

                if (a->zoom < 0.05f) a->zoom = 0.05f;
                if (a->zoom > 20.0f) a->zoom = 20.0f;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                a->dragging = 1;
                a->last_x = e.button.x;
                a->last_y = e.button.y;
            }

            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                a->dragging = 0;
            }

            if (e.type == SDL_MOUSEMOTION && a->dragging) {
                a->offset_x += e.motion.x - a->last_x;
                a->offset_y += e.motion.y - a->last_y;
                a->last_x = e.motion.x;
                a->last_y = e.motion.y;
            }

            if (e.type == SDL_MOUSEWHEEL) {
                int mx, my;
                SDL_GetMouseState(&mx, &my);

                float old_zoom = a->zoom;
                if (e.wheel.y > 0) a->zoom *= 1.1f;
                if (e.wheel.y < 0) a->zoom *= 0.9f;

                if (a->zoom < 0.05f) a->zoom = 0.05f;
                if (a->zoom > 20.0f) a->zoom = 20.0f;

                int win_w, win_h;
                SDL_GetWindowSize(a->window, &win_w, &win_h);

                float img_cx = win_w / 2 + a->offset_x;
                float img_cy = win_h / 2 + a->offset_y;

                a->offset_x = (img_cx - mx) * (a->zoom / old_zoom) + mx - win_w / 2;
                a->offset_y = (img_cy - my) * (a->zoom / old_zoom) + my - win_h / 2;
            }
        }
        draw(a);
    }
}

void app_destroy(app *a) {
    if (a->texture) SDL_DestroyTexture(a->texture);
    if (a->renderer) SDL_DestroyRenderer(a->renderer);
    if (a->window) SDL_DestroyWindow(a->window);
    IMG_Quit();
    SDL_Quit();
}
