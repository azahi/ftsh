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
#include <minishell.h>
# include <libft.h>

int	envadd(t_elist **elist, char *key, char *val)
{
	t_elist	*local;

	local = *elist;
	if (*elist)
	{
		while(local->next)
			local = local->next;
		if (!(local->next = ft_memalloc(sizeof(t_elist))))
			fail();
		local->next->key = key;
		local->next->val = val;
	}
	else
	{
		if (!(*elist = ft_memalloc(sizeof(t_elist))))
			fail();
		(*elist)->key = key;
		(*elist)->val = val;
	}
	return (0);
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
