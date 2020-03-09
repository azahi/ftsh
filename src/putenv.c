/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 21:20:33 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/03/09 21:20:33 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdlib.h>
#include <ft_string.h>

#include "env.h"

static int	env_putenv_norme(char *r, char ***oe, char ***ne, int i)
{
	free(*oe);
	(*ne)[i + 1] = NULL;
	*oe = *ne;
	environ = *oe;
	if (r)
		env_rm_add(0, r);
	return (0);
}

static char	*env_putenv_tmp(char ***e, char *s)
{
	char	*tmp;

	tmp = **e;
	**e = s;
	return (tmp);
}

int			env_putenv(char *s, size_t l, char *r)
{
	size_t		i;
	static char	**oe;
	char		**ne;
	char		**e;

	if (!(i = 0) && environ)
	{
		e = environ;
		while (*e)
		{
			if (!ft_strncmp(s, *e, l + 1))
			{
				env_rm_add(env_putenv_tmp(&e, s), r);
				return (0);
			}
			e++;
			i++;
		}
	}
	if (!(ne = malloc(sizeof(*ne) * (i + 2))))
		return (-1);
	if (i)
		ft_memcpy(ne, environ, sizeof(*ne) * (i + (environ == oe) * 2));
	ne[i] = s;
	return (env_putenv_norme(r, &oe, &ne, i));
}
