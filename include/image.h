// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j

#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

SDL_Texture *image_load(SDL_Renderer *renderer, const char *path, int *w, int *h);

#endif
