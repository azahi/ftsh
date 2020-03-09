/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:13:03 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 19:25:33 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "builtin/builtin.h"
#include "env.h"
#include "exec.h"

static int	exec_proc(char *file, char **argv)
{
	int		wstatus;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(file, argv, environ);
		exit(0);
	}
	else if (pid < 0)
	{
		ufputs(FT_STDERR, "minishell: failed to create a new process.\n");
		return (1);
	}
	else
		waitpid(pid, &wstatus, WUNTRACED);
	return (0);
}

static int	can_exec(char *file)
{
	struct stat	st;

	if (!stat(file, &st) && (st.st_mode & S_IXUSR))
		return (1);
	return (0);
}

static int	err_norme(const char *s)
{
	ufputs(FT_STDERR, "minishell: command not found: ");
	ufputsn(FT_STDERR, s);
	return (1);
}

static int	sh_exec_file(char **argv, size_t k, size_t l, int first)
{
	const char	*p;
	const char	*z;
	char		b[NAME_MAX];

	if ((k = ft_strnlen(argv[0], NAME_MAX + 1)) > NAME_MAX)
		return (1);
	if (!(p = lenv_getenv("PATH")))
		return (err_norme(argv[0]));
	l = ft_strlen(p);
	while ((z = ft_strchrnul(p, ':')) || 1)
	{
		if (!(!first && z - p >= (long)l) && !(first = 0))
		{
			ft_memcpy(b, p, z - p);
			b[z - p] = '/';
			ft_memcpy(b + (z - p) + (z > p), argv[0], k + 1);
			if (can_exec(b))
				return (exec_proc(b, argv));
			if (!*z++ || ((p = z) && 0))
				break ;
		}
		if (!*z++)
			break ;
	}
	return (err_norme(argv[0]));
}

static int	sh_exec_builtin(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (!ft_strcmp(argv[0], g_builtin_names[i]))
			return ((*g_builtin_func[i])(argc, argv));
		i++;
	}
	return (-1);
}

int			sh_exec(int argc, char **argv)
{
	int ret;

	if (!argv[0])
		return (1);
	if ((ret = sh_exec_builtin(argc, argv)) != -1)
		return (ret);
	if (ft_strchr(argv[0], '/') && can_exec(argv[0]))
		return (exec_proc(argv[0], argv));
	return (sh_exec_file(argv, 0, 0, 1));
}
