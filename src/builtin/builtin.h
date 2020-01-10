#ifndef BUILTIN_H
#define BUILTIN_H

/**
 * TODO Make this a little bit more sane-ish
 * The prospect of having multiple functions/datatypes to deal with, possibly,
 * a large number of builtins isn't quite appealing to me.
 * We probably should consider makinga specific structure to deal with it.
 * Probably should even consider someting tree-like.
 */

#define BUILTIN_COUNT 7

int builtin_cd(int argc, char **argv, int *envc, char ***envp);
int builtin_echo(int argc, char **argv, int *envc, char ***envp);
int builtin_env(int argc, char **argv, int *envc, char ***envp);
int builtin_exit(int argc, char **argv, int *envc, char ***envp);
int builtin_pwd(int argc, char **argv, int *envc, char ***envp);
int builtin_setenv(int argc, char **argv, int *envc, char ***envp);
int builtin_unsetenv(int argc, char **argv, int *envc, char ***envp);

char
*builtin_names[] = {
	"cd",
	"echo",
	"env",
	"exit",
	"pwd",
	"setenv",
	"unsetenv"
};

int (*builtin_func[])(int, char **, int *, char ***) = {
	&builtin_cd,
	&builtin_echo,
	&builtin_env,
	&builtin_exit,
	&builtin_pwd,
	&builtin_setenv,
	&builtin_unsetenv
};

#endif /* BUILTIN_H */
