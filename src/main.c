// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j

#include <stdio.h>
#include "../include/app.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: iris <images...>\n");
        return 1;
    }

    app a;
    app_init(&a, argv + 1, argc - 1);
    app_run(&a);
    app_destroy(&a);
    return 0;
}
