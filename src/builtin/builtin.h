#ifndef BUILTIN_H
#define BUILTIN_H

int builtin_cd(int argc, char **argv);
int builtin_echo(int argc, char **argv);
int builtin_env(int argc, char **argv);
int builtin_exit(int argc, char **argv);
int builtin_pwd(int argc, char **argv);
int builtin_setenv(int argc, char **argv);
int builtin_unsetenv(int argc, char **argv);

#endif /* BUILTIN_H */
