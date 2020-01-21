#include <ft_stdlib.h>
#include <ft_string.h>

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

char *
lenv_getenv(const char *name)
{
	char **env = g_env;
	size_t l = ft_strchrnul(name, '=') - name;
	if (l && !name[l] && env)
	{
		env = g_env;
		while (*env)
		{
			if (!ft_strncmp(name, *env, l) && l[*env] == '=')
				return (*env + l + 1);
			env++;
		}
	}
	return (NULL);
}

/**
 * Initialization of local environment table.
 * Note: This will utilize a global variable because we will need it in order
 * to be able to make a clean exit from a program once we encounter a error
 * during runtime.
 * Also for convenience because fuck 42's subjects anyway.
 *
 * FIXME Something goes horribly wrong in here: a first section gets rewritten
 * and filled with gibberish. Not sure what's the case here yet.
 */
void
lenv_init(void)
{
	extern char	**environ;
	int			size;
	int			i;

	size = get_arr_size(environ);
	if (!(g_env = malloc(sizeof (**g_env) * size)))
	{
		// TODO Clean exit
		return ;
	}
	i = 0;
	while (i < size)
	{
		g_env[i] = strdup(environ[i]); // FIXME Replace
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
	free(e);
	e = NULL;
	g_env = NULL;
}
