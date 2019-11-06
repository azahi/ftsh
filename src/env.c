/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:40:52 by jdeathlo          #+#    #+#             */
/*   Updated: 2019/11/06 22:06:08 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <stdlib.h>

int	envadd(t_elist **elist, char *key, char *val)
{
	t_elist	*local;

	if (!(local = malloc(sizeof(t_elist))))
		fail();
	local->key = key;
	local->val = val;
	local->next = *elist;
	*elist = local;
}

void	array_to_lst(char **env, t_elist **elist)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		envadd(elist, ft_strndup(env[i], j), ft_strdup(&(env[i][j + 1])));
		i++;
	}
}
