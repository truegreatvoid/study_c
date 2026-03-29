#include "app_config.h"
#include "env.h"
#include <string.h>
#include <stdlib.h>

static AppConfig config;

static void copy_or_default(char *dest, size_t size, const char *value, const char *fallback) {
    const char *src = value ? value : fallback;
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

int app_config_init(const char *env_file) {
    env_load(env_file);

    copy_or_default(config.app_name, sizeof(config.app_name), env_get("APP_NAME"), "VIVA SEGURA");
    copy_or_default(config.db_host, sizeof(config.db_host), env_get("DB_HOST"), "127.0.0.1");
    copy_or_default(config.db_user, sizeof(config.db_user), env_get("DB_USER"), "app");
    copy_or_default(config.db_pass, sizeof(config.db_pass), env_get("DB_PASS"), "app");
    copy_or_default(config.db_name, sizeof(config.db_name), env_get("DB_NAME"), "viva_segura");

    config.db_port = (unsigned int) atoi(env_get("DB_PORT") ? env_get("DB_PORT") : "3306");
    config.ui_use_color = atoi(env_get("UI_USE_COLOR") ? env_get("UI_USE_COLOR") : "1");
    config.ui_primary = atoi(env_get("UI_PRIMARY") ? env_get("UI_PRIMARY") : "36");
    config.ui_success = atoi(env_get("UI_SUCCESS") ? env_get("UI_SUCCESS") : "32");
    config.ui_error = atoi(env_get("UI_ERROR") ? env_get("UI_ERROR") : "31");
    config.ui_warning = atoi(env_get("UI_WARNING") ? env_get("UI_WARNING") : "33");

    return 1;
}

const AppConfig *app_config_get(void) {
    return &config;
}