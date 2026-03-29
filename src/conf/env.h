#ifndef ENV_H
#define ENV_H

int env_load(const char *filename);
const char *env_get(const char *key);

#endif