#ifndef __ENV_H__
#define __ENV_H__

char **g_env;

char *lenv_getenv(const char *);

int lenv_setenv(char *, char *, int);
int lenv_unsetenv(char *);

void lenv_init(void);
void lenv_deinit(void);

#endif /* !__ENV_H__ */
