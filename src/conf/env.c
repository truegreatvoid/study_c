#include "env.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENV_MAX_ITEMS 100
#define ENV_KEY_SIZE 64
#define ENV_VALUE_SIZE 256

typedef struct {
    char key[ENV_KEY_SIZE];
    char value[ENV_VALUE_SIZE];
} EnvItem;

static EnvItem env_items[ENV_MAX_ITEMS];
static int env_count = 0;

static void trim_newline(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

int env_load(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 0;
    }

    char line[512];

    while (fgets(line, sizeof(line), file) != NULL) {
        trim_newline(line);

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        char *equal = strchr(line, '=');
        if (!equal) {
            continue;
        }

        *equal = '\0';
        char *key = line;
        char *value = equal + 1;

        if (env_count < ENV_MAX_ITEMS) {
            strncpy(env_items[env_count].key, key, ENV_KEY_SIZE - 1);
            env_items[env_count].key[ENV_KEY_SIZE - 1] = '\0';

            strncpy(env_items[env_count].value, value, ENV_VALUE_SIZE - 1);
            env_items[env_count].value[ENV_VALUE_SIZE - 1] = '\0';

            env_count++;
        }
    }

    fclose(file);
    return 1;
}

const char *env_get(const char *key) {
    for (int i = 0; i < env_count; i++) {
        if (strcmp(env_items[i].key, key) == 0) {
            return env_items[i].value;
        }
    }

    return NULL;
}