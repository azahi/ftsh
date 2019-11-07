/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:38:43 by jdeathlo          #+#    #+#             */
/*   Updated: 2019/11/06 21:44:51 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct		s_elist
{
	char			*key;
	char			*val;
	struct s_elist	*next;
}					t_elist;

int		envadd(t_elist **elist, char *key, char *val);
void	array_to_lst(char **env, t_elist **elist);
#endif
