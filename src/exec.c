/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:19:50 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/30 23:51:04 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <sys/wait.h>
#include <uio.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

#include "exec.h"
#include "exec_util.h"

 // FIXME Fix that retarded command not found after fullpath command is
 // done executing.
static int	exec_proc(char *file, char **argv)
{
	int		wstatus;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ft_execv(file, argv);
		exit(0);
	}
	else if (pid < 0)
	{
		ufputs(STDERR_FILENO, "minishell: failed to create a new process.\n");
		return (1);
	}
	else
		waitpid(pid, &wstatus, WUNTRACED);
	return (0);
}

static int	sh_exec_file_path(char **argv)
{
	if (ft_strchr(argv[0], '/'))
	{
		if (!is_file(argv[0]))
			return (1);
		if (can_exec(argv[0]))
			return (exec_proc(argv[0], argv));
		else
		{
			ufputs(STDERR_FILENO, getenv("SHELL"));
			ufputs(STDERR_FILENO, ": permission denied: ");
			ufputsn(STDERR_FILENO, argv[0]);
			return (1);
		}
	}
	return (0);
}

static int	sh_exec_file_pathloop(char *p, size_t pathl, char **argv,
		size_t arg0l)
{
	char	*z;
	char	b[PATH_MAX + NAME_MAX + 1]; // TODO Find a way to make the size smaller with "k + l + 1"
	int		first;

	first = 1;
	while (1)
	{
		z = ft_strchrnul(p, ':');
		if (!first && (size_t)z - (size_t)p >= pathl)
		{
			if (!*z++)
				break ;
			continue;
		}
		first = 0;
		ft_memcpy(b, p, z - p);
		b[z - p] = '/';
		ft_memcpy(b + (z - p) + (z > p), argv[0], arg0l + 1);
		if (can_exec(b))
			return (exec_proc(b, argv));
		if (!*z++)
			break ;
		p = z;
	}
	return (-1);
}

int			sh_exec_file(char **argv)
{
	char		*path;
	int			status;
	size_t		arg0l;
	size_t		pathl;

	if (sh_exec_file_path(argv))
		return (1);
	if ((arg0l = ft_strnlen(argv[0], NAME_MAX + 1)) > NAME_MAX)
		return (1);
	if (!(path = ft_getenv("PATH")))
		return (sh_exec_file_errnotfound(argv[0]));
	pathl = ft_strlen(path);
	if ((status = sh_exec_file_pathloop(path, pathl, argv, arg0l)) != -1)
		return (status);
	return (sh_exec_file_errnotfound(argv[0]));
}

int			sh_exec(int argc, char **argv)
{
	int ret;

	if (!argv[0])
		return (1);
	if ((ret = sh_exec_builtin(argc, argv)) != -1)
		return (ret);
	return (sh_exec_file(argv));
}
