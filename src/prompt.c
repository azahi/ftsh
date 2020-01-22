/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:24:04 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/01/22 14:24:12 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>
#include <ft_string.h>
#include <unistd.h>

#include "env.h"
#include "prompt.h"

/*
 * Display a prompt message.
 */

void
prompt(void)
{
	char	*cwd;
	char	*home;
	char	buf[PROMPT_BUF_SIZE + 1];
	size_t	home_l;

	cwd = getcwd(buf, PROMPT_BUF_SIZE);
	home = lenv_getenv("HOME");
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
