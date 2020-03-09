#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif

#ifdef DEBUG
#include <stdio.h>
#endif /* !DEBUG */

#include "builtin/builtin.h"
#include "env.h"
#include "exec.h"

static int
exec_proc(char *file, char **argv)
{
	pid_t pid = fork();
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
	{
		int wstatus;
		waitpid(pid, &wstatus, WUNTRACED);
	}
	return (0);
}

static int
can_exec(char *file)
{
	struct stat st;
	if (!stat(file, &st))
	{
		if (st.st_mode & S_IXUSR)
			return (1);
	}
	return (0);
}

static int
sh_exec_file(char **argv)
{
	if (ft_strchr(argv[0], '/') && can_exec(argv[0]))
		return (exec_proc(argv[0], argv));

	size_t k = ft_strnlen(argv[0], NAME_MAX + 1);
	if (k > NAME_MAX)
		return (1);

	char *path = lenv_getenv("PATH");
	//if (!path)
	//	path = "/usr/local/bin:/usr/bin:/bin";
	if (!path)
	{
		ufputs(FT_STDERR, "minishell: command not found: ");
		ufputsn(FT_STDERR, argv[0]);
		return (1);
	}
	size_t l = ft_strlen(path);

	const char *p = path, *z;
	while (1)
	{
		char b[l + k + 1]; /* Not norm-like */
		z = ft_strchrnul(p, ':');
		if (z - p >= (long)l)
		{
			if (!*z++)
				break;
			continue;
		}
		ft_memcpy(b, p, z - p);
		b[z - p] = '/';
		ft_memcpy(b + (z - p) + (z > p), argv[0], k + 1);
		if (can_exec(b))
			return (exec_proc(b, argv));
		if (!*z++)
			break;
		p = z;
	}
	ufputs(FT_STDERR, "minishell: command not found: ");
	ufputsn(FT_STDERR, argv[0]);
	return (1);
}

static int
sh_exec_builtin(int argc, char **argv)
{
	int i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (!ft_strcmp(argv[0], builtin_names[i]))
		{
#ifdef DEBUG
			fprintf(stderr, "sh_exec_builtin(%d", argc);
			for (int j = 0; j < argc; j++)
				fprintf(stderr, ", \"%s\"", argv[j]);
			fprintf(stderr, "): %p => OK\n", *(builtin_func)[i]);
#endif /* !DEBUG */
			return ((*builtin_func[i])(argc, argv));
		}
		i++;
	}
	return (-1);
}

int
sh_exec(int argc, char **argv)
{
	if (!argv[0])
		return (1);
	int ret;
	if ((ret = sh_exec_builtin(argc, argv)) != -1)
		return (ret);
	return (sh_exec_file(argv));
}
