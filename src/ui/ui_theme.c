#include "ui_theme.h"
#include "../conf/app_config.h"
#include <stdio.h>

static void ui_print_color_code(int color, const char *text) {
    const AppConfig *config = app_config_get();

    if (!config->ui_use_color) {
        printf("%s", text);
        return;
    }

    printf("\033[%dm%s\033[0m", color, text);
}

void ui_print_primary(const char *text) {
    ui_print_color_code(app_config_get()->ui_primary, text);
}

void ui_print_success(const char *text) {
    ui_print_color_code(app_config_get()->ui_success, text);
}

void ui_print_error(const char *text) {
    ui_print_color_code(app_config_get()->ui_error, text);
}

void ui_print_warning(const char *text) {
    ui_print_color_code(app_config_get()->ui_warning, text);
}

void ui_reset(void) {
    printf("\033[0m");
}