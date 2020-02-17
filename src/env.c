#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "env.h"

/**
 * Count the amount of elements in char **environ;
 */
static size_t
arr_size(char **arr)
{
	size_t i = 0;
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
			{
#ifdef DEBUG
				fprintf(stderr, "lenv_getenv(\"%s\"): \"%s\"\n", name, *env + l + 1);
#endif
				return (*env + l + 1);
			}
			env++;
		}
	}
#ifdef DEBUG
	fprintf(stderr, "lenv_getenv(\"%s\"): NULL\n", name);
#endif
	return (NULL);
}

/**
 * Check if key exists in environment table, unset and recreate the table.
 */
void
lenv_unset(char *key)
{
	(void)key;
}

/**
 * Add to back or replace the environment variable
 */
void
lenv_set(char *key, char *val)
{
	(void)key;
	(void)val;
}

/**
 * Initialization of local environment table.
 * Note: This will utilize a global variable because we will need it in order
 * to be able to make a clean exit from a program once we encounter a error
 * during runtime.
 * Also for convenience because fuck 42's subjects anyway.
 */
void
lenv_init(void)
{
	extern char	**environ;
	int size = arr_size(environ);
	if (!(g_env = malloc(sizeof (char *) * (size + 1))))
		exit(EXIT_FAILURE);
	int i = 0;
	while (i < size)
	{
		g_env[i] = ft_strdup(environ[i]);
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
	char **env = g_env;
	while (*env)
	{
		free(*env);
		env++;
	}
	free(g_env);
}
