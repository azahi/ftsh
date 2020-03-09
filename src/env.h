#ifndef __ENV_H__
#define __ENV_H__

#define EXTERN_CHAR_ENVIRON extern char **environ

EXTERN_CHAR_ENVIRON;

char *lenv_getenv(const char *);

int lenv_setenv(const char *, const char *, int);
int lenv_unsetenv(const char *);

#endif /* !__ENV_H__ */
