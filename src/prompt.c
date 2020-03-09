/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:34:19 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 19:26:01 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _GNU_SOURCE
#endif

#include <ft.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <limits.h>

#include "env.h"
#include "prompt.h"

#define HOSTNAME_SIZE 64

void	prompt(void)
{
	char	host[HOSTNAME_SIZE];
	char	buf[PATH_MAX + 1];
	char	*cwd;
	char	*home;
	size_t	home_l;

	home = lenv_getenv("HOME");
	cwd = getcwd(buf, PATH_MAX);
	home_l = ft_strlen(home);
	ufputs(FT_STDOUT, lenv_getenv("USER"));
	if (!gethostname(host, HOSTNAME_SIZE))
	{
		ufputc(FT_STDOUT, '@');
		ufputs(FT_STDOUT, host);
	}
	ufputc(FT_STDOUT, ':');
	if (!ft_strncmp(cwd, home, home_l))
	{
		ufputc(FT_STDOUT, '~');
		ufputs(FT_STDOUT, cwd + home_l);
	}
	else
		ufputs(FT_STDOUT, cwd);
	ufputs(FT_STDOUT, " $ ");
}

#ifdef _GNU_SOURCE
# undef _GNU_SOURCE
#endif
