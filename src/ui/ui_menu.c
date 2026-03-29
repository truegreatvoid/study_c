#include "ui_menu.h"
#include "ui_theme.h"
#include "../shared/navigation.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#define KEY_UP 1001
#define KEY_DOWN 1002

static void ui_clear_screen_internal(void) {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
    fflush(stdout);
#endif
}

#ifndef _WIN32
static int read_key_linux(void) {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_iflag &= ~(IXON | ICRNL);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    if (ch == 27) {
        int ch1 = getchar();

        if (ch1 == '[') {
            int ch2 = getchar();

            if (ch2 == 'A') {
                ch = KEY_UP;
            } else if (ch2 == 'B') {
                ch = KEY_DOWN;
            } else {
                ch = 27;
            }
        } else {
            ch = 27;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#ifdef _WIN32
static int read_key_windows(void) {
    int ch = _getch();

    if (ch == 224 || ch == 0) {
        ch = _getch();

        if (ch == 72) return KEY_UP;
        if (ch == 80) return KEY_DOWN;
    }

    return ch;
}
#endif

static int read_key(void) {
#ifdef _WIN32
    return read_key_windows();
#else
    return read_key_linux();
#endif
}

int ui_menu_select(const char *title, const char *options[], int count) {
    int selected = 0;

    while (1) {
        ui_clear_screen_internal();

        ui_print_primary("=====================================\n");
        printf("%s\n", title);
        ui_print_primary("=====================================\n\n");

        for (int i = 0; i < count; i++) {
            if (i == selected) {
                ui_print_primary(" > ");
                printf("%s\n", options[i]);
            } else {
                printf("   %s\n", options[i]);
            }
        }

        printf("\n");
        ui_print_warning("Use ↑ ↓ e Enter.\n");
        ui_print_warning("ESC = voltar\n");

        int key = read_key();

        if (key == 27) {
            return NAV_BACK;
        } else if (key == KEY_UP) {
            selected--;
            if (selected < 0) {
                selected = count - 1;
            }
        } else if (key == KEY_DOWN) {
            selected++;
            if (selected >= count) {
                selected = 0;
            }
        } else if (key == '\n' || key == '\r') {
            return selected;
        }
    }
}