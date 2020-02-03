#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft.h>

#include "env.h"

/**
 * Count the amount of elements in char **environ;
 */
static size_t
get_arr_size(char **arr)
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
				return (*env + l + 1);
			env++;
		}
	}
	return (NULL);
}

/**
 * Check if key exists in environment table, unset and recreate the table.
 */
void
lenv_unset(char *key)
{
	size_t key_size = ft_strlen(key) + 1;
	char *lkey = malloc(sizeof (*lkey) * key_size);
	lkey = strcat(key, "=");
	size_t i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], lkey, key_size))
			break;
		i++;
	}
	size_t size = get_arr_size(g_env) - 1;
	if (i == size)
		return;
	char **env = malloc(sizeof(char *) * (size + 1));
	size_t j = 0;
	while (j < size)
	{
		if (j != i)
			ft_memmove(env[j], g_env[j], ft_strlen(g_env[j]));
		j++;
	}
}

/**
 * Add to back or replace the environment variable
 */
void
lenv_set(char *key, char *val)
{
	size_t size = get_arr_size(g_env) + 1;
	g_env = realloc(g_env, size);
	size_t var_size = strlen(key) + 1 + strlen(val);
	char *var = malloc(sizeof (*var) * var_size);
	memset(var, '\0', var_size);
	strcat(var, key);
	strcat(var, "=");
	strcat(var, val);
	g_env[size - 1] = var;
	g_env[size] = NULL;
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
	int			size;
	int			i;

	size = get_arr_size(environ);
	if (!(g_env = malloc(sizeof (char *) * (size + 1))))
		exit(1);
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
	char **env = g_env;
	while (*env)
	{
		free(*env);
		env++;
	}
	free(env);
}
