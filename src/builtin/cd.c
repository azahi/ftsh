/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:06:04 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/28 11:12:28 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic ignored "-Wunused-result"

#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <uio.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static int	err(char *target)
{
	ufputs(STDERR_FILENO, "cd: error: ");
	ufputsn(STDERR_FILENO, target);
	return (1);
}

int			builtin_cd(int argc, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	buf[PATH_MAX];

	(void)argc;
	target = argv[1];
	if (!getcwd(buf, sizeof(buf)))
		return (err(target));
	oldpwd = ft_getenv("OLDPWD");
	if (!oldpwd)
		oldpwd = ft_strdup(buf);
	if (!target)
		target = ft_getenv("HOME");
	else if (!ft_strcmp(target, "-"))
	{
		ufputsn(STDERR_FILENO, oldpwd);
		target = oldpwd;
	}
	if (chdir(target) == -1)
		return (err(target));
	ft_setenv("OLDPWD", buf, 1);
	getcwd(buf, sizeof(buf));
	ft_setenv("PWD", buf, 1);
	return (0);
}
