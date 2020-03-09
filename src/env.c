#include <ft_stdlib.h>
#include <ft_string.h>

#ifdef DEBUG
#include <stdio.h>
#endif /* !DEBUG */

#include "env.h"

/**
 * Environment modification routine.
 */
static void
env_rm_add(char *old, char *new)
{
	static char **env_alloced;
	static size_t env_alloced_n;
	for (size_t i = 0; i < env_alloced_n; i++)
	{
		if (env_alloced[i] == old)
		{
			env_alloced[i] = new;
			free(old);
			return;
		}
		else if (!env_alloced[i] && new)
		{
			env_alloced[i] = new;
			new = 0;
		}
	}
	if (!new)
		return;
	char **t;
	if (!(t = malloc(sizeof (*t) * (env_alloced_n + 1))))
		return;
	for (size_t j = 0; j < env_alloced_n; j++)
		t[j] = env_alloced[j];
	free(env_alloced);
	(env_alloced = t)[env_alloced_n++] = new;
}

/**
 * Internal implementation of putnev(3)
 */
static int
env_putenv(char *s, size_t l, char *r)
{
	size_t i = 0;
	if (environ)
	{
		for (char **e = environ; *e; e++, i++)
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
	if (environ == oldenv)
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
			ft_memcpy(newenv, environ, sizeof (*newenv) * i);
		free(oldenv);
	}
	newenv[i] = s;
	newenv[i + 1] = 0;
	environ = oldenv = newenv;
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
	char **env = environ;
	size_t l = ft_strchrnul(name, '=') - name;
	if (l && !name[l] && env)
	{
		env = environ;
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
int
lenv_setenv(const char *key, const char *val, int overwrite)
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
int
lenv_unsetenv(const char *name)
{
	size_t l = ft_strchrnul(name, '=') - name;
	if (!l || name[l])
		return (-1);
	if (environ)
	{
		char **e = environ, **eo = e;
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
