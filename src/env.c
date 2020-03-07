/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:47:04 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/07 21:21:44 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdlib.h>
#include <ft_string.h>
#include "env.h"

static void	env_rm_add(char *old, char *new)
{
	static char		**env_alloced;
	static size_t	env_alloced_n;
	int				i;
	char			**t;

	i = -1;
	while ((i++ || 1) && i < (int)env_alloced_n)
		if (env_alloced[i] == old)
		{
			env_alloced[i] = new;
			free(old);
			return ;
		}
		else if (!env_alloced[i] && new)
		{
			env_alloced[i] = new;
			new = 0;
		}
	if (!new || !(t = malloc(sizeof(*t) * (env_alloced_n + 1))))
		return ;
	i = -1;
	while ((i++ || 1) && i < (int)env_alloced_n)
		t[i] = env_alloced[i];
	free(env_alloced);
	env_alloced = t;
	t[env_alloced_n++] = new;
}

/**
 * Internal implementation of putnev(3)
 */
static int	env_putenv(char *s, size_t l, char *r)
{
	size_t i = 0;
	if (g_env)
	{
		for (char **e = g_env; *e; e++, i++)
		{
			if (!ft_strncmp(s, *e, l + 1))
			{
				char *tmp = *e;
				*e = s;
				env_rm_add(tmp, r);
				return (0);
			}
		}
	}
	static char **oldenv;
	char **newenv;
	if (g_env == oldenv)
	{
		newenv = malloc(sizeof (*newenv) * (i + 2));
		if (!newenv)
		{
			free(r);
			return (-1);
		}
		for (size_t j = 0; j < i + 2; j++)
			newenv[j] = oldenv[j];
		free(oldenv);
	}
	else
	{
		newenv = malloc(sizeof (*newenv) * (i + 2));
		if (!newenv)
		{
			free(r);
			return (-1);
		}
		if (i)
			ft_memcpy(newenv, g_env, sizeof (*newenv) * i);
		free(oldenv);
	}
	newenv[i] = s;
	newenv[i + 1] = 0;
	g_env = oldenv = newenv;
	if (r)
		env_rm_add(0, r);
	return (0);
}

/**
 * getenv(3)
 */
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
#endif /* !DEBUG */
				return (*env + l + 1);
			}
			env++;
		}
	}
#ifdef DEBUG
	fprintf(stderr, "DEBUG: lenv_getenv(\"%s\"): (null)\n", name);
#endif /* !DEBUG */
	return (NULL);
}

/**
 * setenv(3)
 */
int 	lenv_setenv(char *key, char *val, int overwrite)
{
	size_t kp;
	if (!key || !(kp = ft_strchrnul(key, '=') - key) || key[kp])
		return (-1);
	if (!overwrite && lenv_getenv(key))
		return (0);

	size_t vp = ft_strlen(val);
	char *s = malloc(kp + vp + 2);
	if (!s)
		return (-1);

	ft_memcpy(s, key, kp);
	s[kp] = '=';
	ft_memcpy(s + kp + 1, val, vp + 1);
	return (env_putenv(s, kp, s));
}

/**
 * unsetenv(3)
 */
int		lenv_unsetenv(char *name)
{
	size_t l = ft_strchrnul(name, '=') - name;
	if (!l || name[l])
		return (-1);
	if (g_env)
	{
		char **e = g_env, **eo = e;
		for (; *e; e++)
		{
			if (!ft_strncmp(name, *e, l) && l[*e] == '=')
				env_rm_add(*e, 0);
			else if (eo != e)
				*eo++ = *e;
			else
				eo++;
		}
		if (eo != e)
			*eo = 0;
	}
	return (0);
}

/**
 * Initialize the local environment table.
 */
void
lenv_init(void)
{
	extern char	**environ;
	int size = 0;
	while (environ[size])
		size++;
	if (!(g_env = malloc(sizeof (char *) * (size + 1))))
		exit(1);
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
#endif /* !DEBUG */
}

/**
 * Destroy the local environment table.
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
#endif /* !DEBUG */
}
