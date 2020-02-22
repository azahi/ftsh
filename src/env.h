#ifndef __ENV_H__
#define __ENV_H__

char **g_env;

char *lenv_getenv(const char *name);

int lenv_set(char *key, char *val);
int lenv_unset(char *key);

void lenv_init(void);
void lenv_deinit(void);

#endif /* !__ENV_H__ */
