#ifndef ENV_H
#define ENV_H

char **g_env;

char *lenv_getenv(const char *name);

void lenv_set(char *key, char *val);
void lenv_unset(char *key);

void lenv_init(void);
void lenv_deinit(void);

#endif
