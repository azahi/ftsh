/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:06:33 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/28 11:06:37 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uio.h>

int	builtin_env(int argc, char **argv)
{
	extern char	**environ;
	char		**e;

	(void)argc;
	(void)argv;
	e = environ;
	while (*e)
	{
		uputsn(*e);
		e++;
	}
	return (0);
}
