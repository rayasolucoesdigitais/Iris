// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

static void fail(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

SDL_Texture *image_load(SDL_Renderer *renderer, const char *path, int *w, int *h) {
    SDL_Surface *img = IMG_Load(path);
    if (!img) fail(IMG_GetError());

    *w = img->w;
    *h = img->h;

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    if (!tex) fail(SDL_GetError());
    return tex;
}
