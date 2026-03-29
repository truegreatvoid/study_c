#include "ui_loading.h"

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

static void sleep_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void ui_loading(const char *message, int steps, int delay_ms) {
    const char spinner[] = "|/-\\";
    int i;

    printf("%s ", message);
    fflush(stdout);

    for (i = 0; i < steps; i++) {
        printf("\r%s %c", message, spinner[i % 4]);
        fflush(stdout);
        sleep_ms(delay_ms);
    }

    printf("\r%s concluído.    \n", message);
    fflush(stdout);
}