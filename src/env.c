/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:47:04 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 21:17:14 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdlib.h>
#include <ft_string.h>

#include "env.h"
#include "putenv.h"

void		env_rm_add(char *old, char *new)
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
			return (free(old));
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

char		*lenv_getenv(const char *name)
{
	char	**env;
	size_t	l;

	env = environ;
	l = ft_strchrnul(name, '=') - name;
	if (l && !name[l] && env)
	{
		env = environ;
		while (*env)
		{
			if (!ft_strncmp(name, *env, l) && l[*env] == '=')
				return (*env + l + 1);
			env++;
		}
	}
	return (NULL);
}

int			lenv_setenv(const char *key, const char *val, int overwrite)
{
	size_t	kp;
	size_t	vp;
	char	*s;

	if (!key || !(kp = ft_strchrnul(key, '=') - key) || key[kp])
		return (-1);
	if (!overwrite && lenv_getenv(key))
		return (0);
	vp = ft_strlen(val);
	s = malloc(kp + vp + 2);
	if (!s)
		return (-1);
	ft_memcpy(s, key, kp);
	s[kp] = '=';
	ft_memcpy(s + kp + 1, val, vp + 1);
	return (env_putenv(s, kp, s));
}

int			lenv_unsetenv(const char *name)
{
	size_t	l;
	char	**e;
	char	**eo;

	l = ft_strchrnul(name, '=') - name;
	if (!l || name[l])
		return (-1);
	if (environ)
	{
		e = environ;
		eo = e;
		while (*e)
		{
			if (!ft_strncmp(name, *e, l) && l[*e] == '=')
				env_rm_add(*e, 0);
			else if (eo != e)
				*eo++ = *e;
			else
				eo++;
			e++;
		}
		if (eo != e)
			*eo = 0;
	}
	return (0);
}
