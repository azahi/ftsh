/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:15:52 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/29 13:50:43 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_unistd.h>
#include <uio.h>

#include "loop.h"

static void	print_version(void)
{
	uputs(SH_NAME);
	uputs(", version ");
	uputsn(SH_VERSION);
	exit(EXIT_SUCCESS);
}

static void	print_usage(void)
{
	uputs("Usage: ");
	uputs(SH_NAME);
	uputs(" [-vh]\n");
	uputs("  -v  Print version\n");
	uputs("  -h  Print this message\n");
	exit(EXIT_SUCCESS);
}

static void	sh_getopt(int *argc, char ***argv)
{
	char	ch;

	while ((ch = ft_getopt(*argc, *argv, "vh")) != -1)
	{
		if (ch == 'v')
			print_version();
		else if (ch == 'h')
			print_usage();
		else
			print_usage();
	}
	*argc -= g_optind;
	*argv += g_optind;
}

int			main(int argc, char **argv)
{
	char	*shell;

	shell = argv[0];
	sh_getopt(&argc, &argv);
	ft_setenv("SHELL", shell, 1);
	sh_loop();
}
