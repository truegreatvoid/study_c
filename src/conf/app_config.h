#ifndef APP_CONFIG_H
#define APP_CONFIG_H

typedef struct {
    char app_name[100];
    char db_host[100];
    char db_user[100];
    char db_pass[100];
    char db_name[100];
    unsigned int db_port;
    int ui_use_color;
    int ui_primary;
    int ui_success;
    int ui_error;
    int ui_warning;
} AppConfig;

int app_config_init(const char *env_file);
const AppConfig *app_config_get(void);

#endif