#include <stdlib.h>
#include <string.h>
#include "env.h"

/**
 * Count the amount of elements in char **environ;
 */
static int
get_arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/**
 * Initialization of local environment table.
 * Note: This will utilize a global variable because we will need it
 * in order to be able to make a clean exit from a program once we
 * encounter a error during runtime.
 * Also for convenience because fuck 42's subjects anyway.
 */
void
lenv_init(void)
{
	extern char	**environ;
	int			size;
	int			i;

	size = get_arr_size(environ);
	g_env = malloc(sizeof (**g_env) * (size + 1));
	i = 0;
	while (i < size)
	{
		g_env[i] = strdup(environ[i]); // FIXME Not allowed
		i++;
	}
	g_env[size] = NULL;
}

/**
 * Destroy the allocated environment table.
 */
void
lenv_deinit(void)
{
	char **e;

	e = g_env;
	while (*e)
	{
		free(*e);
		*e = NULL;
		e++;
	}
	free(g_env);
	g_env = NULL;
}
