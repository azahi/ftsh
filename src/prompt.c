/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:15:20 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/28 12:44:53 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <uio.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

#include "prompt.h"

#ifdef _POSIX_HOST_NAME_MAX
# define HOSTNAME_SIZE _POSIX_HOST_NAME_MAX
#else
# define HOSTNAME_SIZE 255
#endif

static void	prompt_full(void)
{
	char	*cwd;
	char	*home;
	char	buf[PATH_MAX + 1];
	char	host[HOSTNAME_SIZE];
	size_t	home_l;

	uputs(ft_getenv("USER"));
	if (!gethostname(host, HOSTNAME_SIZE))
	{
		uputc('@');
		uputs(host);
	}
	uputc(':');
	cwd = getcwd(buf, PATH_MAX);
	home = ft_getenv("HOME");
	home_l = ft_strlen(home);
	if (!ft_strncmp(cwd, home, home_l))
	{
		uputc('~');
		uputs(cwd + home_l);
	}
	else
		uputs(cwd);
	uputs(" $ ");
}

void		prompt(void)
{
	if (!ft_getenv("HOME") || !ft_getenv("USER"))
		uputs("$> ");
	else
		prompt_full();
}
