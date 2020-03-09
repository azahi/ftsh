/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:22:14 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 21:04:45 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <signal.h>

#include "env.h"
#include "exec.h"
#include "parser.h"
#include "prompt.h"

static void	sigint_shell(int sig)
{
	(void)sig;
	ufputc(FT_STDOUT, '\n');
	prompt();
}

static void	free_lv(char ***lv)
{
	char **lvp;

	lvp = *lv;
	while (*lvp)
	{
		free(*lvp);
		lvp++;
	}
	free(*lv);
}

int			main(int argc, char **argv)
{
	char	*line;
	int		lc;
	char	**lv;
	int		status;

	(void)argc;
	lenv_setenv("SHELL", argv[0], 1);
	while (1)
	{
		signal(SIGINT, sigint_shell);
		prompt();
		if (ugetline(FT_STDIN, &line) != 1)
		{
			ufputc(FT_STDOUT, '\n');
			exit(EXIT_FAILURE);
		}
		lv = sh_split(line, &lc);
		free(line);
		if (!lv)
			exit(EXIT_FAILURE);
		status = sh_exec(lc, lv);
		free_lv(&lv);
		if (status == -10)
			exit(EXIT_SUCCESS);
	}
}
