/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:28:55 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 19:24:09 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>
#include <ft_string.h>
#include <ft_unistd.h>

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
			ufputs(FT_STDOUT, *argv);
			ufputc(FT_STDOUT, ' ');
			argv++;
		}
	}
	if (!nonl)
		ufputc(FT_STDOUT, '\n');
	return (0);
}
