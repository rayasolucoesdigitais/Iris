// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j

#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    int img_w;
    int img_h;

    float zoom;
    float offset_x;
    float offset_y;

    double rotation;
    SDL_RendererFlip flip;

    int dragging;
    int last_x;
    int last_y;

    char **files;
    int file_count;
    int file_index;
} app;

void app_init(app *a, char **files, int count);
void app_run(app *a);
void app_destroy(app *a);

#endif
