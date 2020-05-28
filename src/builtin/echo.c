/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:06:07 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/28 11:06:42 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <uio.h>

int	builtin_echo(int argc, char **argv)
{
	int nonl;

	(void)argc;
	nonl = 0;
	if (argv[1])
	{
		argv++;
		if (!ft_strcmp(*argv, "-n"))
		{
			nonl = 1;
			argv++;
		}
		while (*argv)
		{
			uputs(*argv);
			if (*(argv + 1))
				uputc(' ');
			argv++;
		}
	}
	if (!nonl)
		uputc('\n');
	return (0);
}
