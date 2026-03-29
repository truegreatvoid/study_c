#include "platform.h"
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

int is_windows(void) {
#ifdef _WIN32
    return 1;
#else
    return 0;
#endif
}

void setup_platform(void) {
    setlocale(LC_ALL, "");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}