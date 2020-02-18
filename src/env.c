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
				fprintf(stderr, "DEBUG: lenv_getenv(\"%s\"): \"%s\"\n",
						name, *env + l + 1);
#endif
				return (*env + l + 1);
			}
			env++;
		}
	}
#ifdef DEBUG
	fprintf(stderr, "DEBUG: lenv_getenv(\"%s\"): (null)\n", name);
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
	size_t ks = strlen(key);
	size_t vs = strlen(val);
#ifdef DEBUG
	fprintf(stderr, "DEBUG: ks = %lu, vs = %lu\n", ks, vs);
#endif
	char *var = calloc(1, sizeof (*var) * (ks + 1 + vs));
	memcpy(var, key, ks);
#ifdef DEBUG
	fprintf(stderr, "DEBUG: lenv_set(\"%s\", \"%s\"): var = \"%s\"\n", key, val, var);
#endif
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
#ifdef DEBUG
	fprintf(stderr, "DEBUG: lenv_init(): [0] = \"%s\" [%d] = \"%s\" [%d] = \"%s\"\n",
			g_env[0], size - 1, g_env[size - 1], size, g_env[size]);
#endif
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
#ifdef DEBUG
	fprintf(stderr, "DEBUG: lenv_deinit(): OK\n");
#endif
}
