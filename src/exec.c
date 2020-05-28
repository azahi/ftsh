#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <uio.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

#include "builtin/builtin.h"
#include "exec.h"

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

static int	can_exec(char *file)
{
	struct stat	st;

	if (!stat(file, &st))
	{
		if (st.st_mode & S_IXUSR)
			return (1);
	}
	return (0);
}

int			sh_exec_file(char **argv)
{
	char		*path;
	char		b[PATH_MAX + NAME_MAX + 1];
	const char	*p;
	const char	*z;
	int			first;
	size_t		k;
	size_t		l;

	if (ft_strchr(argv[0], '/') && can_exec(argv[0]))
		return (exec_proc(argv[0], argv));
	k = ft_strnlen(argv[0], NAME_MAX + 1);
	if (k > NAME_MAX)
		return (1);
	path = ft_getenv("PATH");
	if (!path)
	{
		ufputs(STDERR_FILENO, "minishell: command not found: ");
		ufputsn(STDERR_FILENO, argv[0]);
		return (1);
	}
	l = ft_strlen(path);
	p = path;
	first = 1;
	while (1)
	{
		z = ft_strchrnul(p, ':');
		if (!first && (size_t)z - (size_t)p >= l)
		{
			if (!*z++)
				break;
			continue;
		}
		first = 0;
		ft_memcpy(b, p, z - p);
		b[z - p] = '/';
		ft_memcpy(b + (z - p) + (z > p), argv[0], k + 1);
		if (can_exec(b))
			return (exec_proc(b, argv));
		if (!*z++)
			break;
		p = z;
	}
	ufputs(STDERR_FILENO, "minishell: command not found: ");
	ufputsn(STDERR_FILENO, argv[0]);
	return (1);
}

static int	sh_exec_builtin(int argc, char **argv)
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

int
sh_exec(int argc, char **argv)
{
	int ret;

	if (!argv[0])
		return (1);
	if ((ret = sh_exec_builtin(argc, argv)) != -1)
		return (ret);
	return (sh_exec_file(argv));
}
