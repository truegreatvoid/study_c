#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "navigation.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

static inline void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

#ifdef _WIN32
static inline int io_read_char(void) {
    return _getch();
}
#else
static inline int io_read_char(void) {
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
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
#endif

static inline void ler_linha(const char *mensagem, char *buffer, size_t tamanho) {
    printf("%s", mensagem);
    fflush(stdout);

    if (fgets(buffer, (int)tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else if (tamanho > 0) {
        buffer[0] = '\0';
    }
}

static inline int ler_linha_controlada(
    const char *mensagem,
    char *buffer,
    size_t tamanho,
    int obrigatorio
) {
    size_t len = 0;

    if (tamanho == 0) {
        return 0;
    }

    buffer[0] = '\0';

    printf("%s", mensagem);
    fflush(stdout);

    while (1) {
        int ch = io_read_char();

        if (ch == 27) {
#ifdef _WIN32
            if (_kbhit()) {
                int ch1 = _getch();
                if (ch1 == 91 || ch1 == 224 || ch1 == 0) {
                    if (_kbhit()) {
                        (void)_getch();
                    }
                    continue;
                }
            }
#else
            int ch1 = io_read_char();
            if (ch1 == '[') {
                int ch2 = io_read_char();
                if (ch2 == 'A' || ch2 == 'B' || ch2 == 'C' || ch2 == 'D') {
                    continue;
                }
            }
#endif
            buffer[0] = '\0';
            printf("\n");
            return NAV_BACK;
        }

        if (ch == '\r' || ch == '\n') {
            if (obrigatorio && len == 0) {
                printf("\nEste campo é obrigatório. Tente novamente.\n");
                printf("%s", mensagem);
                fflush(stdout);
                continue;
            }

            buffer[len] = '\0';
            printf("\n");
            return 0;
        }

        if (ch == 127 || ch == 8) {
            if (len > 0) {
                len--;
                buffer[len] = '\0';
                printf("\b \b");
                fflush(stdout);
            }
            continue;
        }

        if (isprint((unsigned char) ch)) {
            if (len < tamanho - 1) {
                buffer[len++] = (char) ch;
                buffer[len] = '\0';
                putchar(ch);
                fflush(stdout);
            }
        }
    }
}

static inline int ler_linha_obrigatoria(
    const char *mensagem,
    char *buffer,
    size_t tamanho
) {
    return ler_linha_controlada(mensagem, buffer, tamanho, 1);
}

static inline int ler_linha_opcional(
    const char *mensagem,
    char *buffer,
    size_t tamanho
) {
    return ler_linha_controlada(mensagem, buffer, tamanho, 0);
}

static inline int ler_linha_edicao(
    const char *mensagem,
    char *buffer,
    size_t tamanho
) {
    return ler_linha_controlada(mensagem, buffer, tamanho, 0);
}

#endif