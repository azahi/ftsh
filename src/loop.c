/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:24:47 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/28 13:26:30 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdlib.h>
#include <signal.h>
#include <uio.h>

#include "exec.h"
#include "prompt.h"
#include "split.h"

static void	sigint_shell()
{
	uputc('\n');
	prompt();
}

static void	sh_loop_clean(char ***plv)
{
	char	**lv;
	char	**lvp;

	lv = *plv;
	lvp = lv;
	while (*lvp)
	{
		ft_free(*lvp);
		lvp++;
	}
	ft_free(lv);
}

static void	sh_loop_exit(int code)
{
	uputc('\n');
	exit(code);
}

int			sh_loop(void)
{
	char	**lv;
	char	*line;
	int		lc;
	int		status;

	signal(SIGINT, sigint_shell);
	while (1)
	{
		prompt();
		line = NULL;
		if (ugetl(&line) == -1)
			sh_loop_exit(EXIT_FAILURE);
		if (!line)
			sh_loop_exit(EXIT_SUCCESS);
		if (!(lv = sh_split(line, &lc)))
		{
			sh_loop_clean(&lv);
			exit(EXIT_FAILURE);
		}
		ft_free(line);
		status = sh_exec(lc, lv);
		sh_loop_clean(&lv);
		if (status == -42)
			exit(EXIT_SUCCESS);
	}
}
