#ifndef ENV_H
#define ENV_H

char **g_env;

char *lenv_getenv(const char *name);
void lenv_deinit(void);
void lenv_init(void);

#endif
