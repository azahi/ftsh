#ifndef BUILTIN_H
# define BUILTIN_H

# define BUILTIN_COUNT 6

int			builtin_cd(int a, char **b);
int			builtin_echo(int a, char **b);
int			builtin_env(int a, char **b);
int			builtin_exit(int a, char **b);
int			builtin_setenv(int a, char **b);
int			builtin_unsetenv(int a, char **b);

const char	*g_builtin_names[] =
{
	"cd",
	"echo",
	"env",
	"exit",
	"setenv",
	"unsetenv"
};

int			(*g_builtin_funcs[])(int, char **) =
{
	&builtin_cd,
	&builtin_echo,
	&builtin_env,
	&builtin_exit,
	&builtin_setenv,
	&builtin_unsetenv
};

#endif
