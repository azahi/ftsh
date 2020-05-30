/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 21:45:46 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/30 21:53:05 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <sys/stat.h>
#include <uio.h>

#include "builtin/builtin.h"

int	is_file(char *file)
{
	struct stat	st;

	if (!(stat(file, &st)))
		return (1);
	ufputs(STDERR_FILENO, ft_getenv("SHELL"));
	ufputs(STDERR_FILENO, ": no such file or directory: ");
	ufputsn(STDERR_FILENO, file);
	return (0);
}

int	can_exec(char *file)
{
	struct stat	st;

	if (!stat(file, &st))
	{
		if (st.st_mode & S_IXUSR)
			return (1);
	}
	return (0);
}

int	sh_exec_file_errnotfound(const char cmd[])
{
	ufputs(STDERR_FILENO, "minishell: command not found: ");
	ufputsn(STDERR_FILENO, cmd);
	return (1);
}

int	sh_exec_builtin(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < g_builtin_count)
	{
		if (!ft_strcmp(argv[0], g_builtin_names[i]))
			return ((*g_builtin_funcs[i])(argc, argv));
		i++;
	}
	return (-1);
}
