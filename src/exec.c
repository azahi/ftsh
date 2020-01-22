#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin/builtin.h"
#include "env.h"
#include "exec.h"
#include "minishell.h"

static char *
getpath(void)
{
	char *path;
	char **env;
	size_t path_len;

	env = g_env;
	while (*env)
	{
		if (!strncmp(*env, "PATH=", 5)) // FIXME Replace
		{
			path_len = strlen(*env) - 5; // FIXME Replace
			if (!(path = malloc(sizeof (*path) * path_len)))
			{
				// TODO Clean exit
				exit(1);
			}
			memmove(path, *env + 5, path_len); // FIXME Replace
			return (path);
		}
		env++;
	}
	return (NULL);
}

/**
 * Executes from PATH.
 */
static int
sh_exec_path(char **argv)
{
	int wstatus;
	pid_t pid;

	char *path = getpath();
	free(path);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1) // TODO Switch to execve
			uputs("execvp failed\n");
		exit(1);
	}
	else if (pid < 0)
	{
		uputs("PID < 0\n");
	}
	else
	{
		do
			waitpid(pid, &wstatus, WUNTRACED);
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
	return (1);
}

int
sh_exec_builtin(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (!strcmp(argv[0], builtin_names[i])) // TODO Replace
			return ((*builtin_func[i])(argc, argv));
		i++;
	}
	return (0);
}

/**
 * Executes a builtin if argv[0] corresponds to an element in builtin array.
 */
int
sh_exec(int argc, char **argv)
{
	int status = 1;

	if (!argv[0])
		return (1);
	if ((status = sh_exec_builtin(argc, argv)))
		return (status);
	return (sh_exec_path(argv));
}
