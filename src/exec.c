#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

#include "builtin/builtin.h"
#include "env.h"
#include "exec.h"
#include "minishell.h"

static int
exec_proc(char *file, char **argv)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		execve(file, argv, g_env);
		exit(1);
	}
	else if (pid < 0)
	{
		uputs("PID < 0\n");
	}
	else
	{
		int wstatus;
		do
			waitpid(pid, &wstatus, WUNTRACED);
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
	return (0);
}

static int
can_exec(char *file)
{
	// TODO stat(2)
	return (1);
}

static int sh_exec_file(int argc, char **argv);
{
	char *file = *argv;

	if (strchr(file, '/'))
	{
		if (can_exec(file))
			return (exec_proc(file, argv));
	}

	size_t file_l = strnlen(file, NAME_MAX + 1);
	if (file_l > NAME_MAX)
		return (-1);

	char *path = lenv_getenv("PATH");
	if (!path)
		path = "/usr/local/bin:/usr/bin:/bin";

	int bufsize = TOK_BUFSIZE;
	char **tokens = malloc(sizeof (**tokens) * bufsize);
	char *token = strtok(path, ":"); // FIXME Replace
	int i = 0;
	while (token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, sizeof (**tokens) * bufsize));
		}
		token = strtok(NULL, ":"); // FIXME Replace
	}
	tokens[i] = NULL;
}

static int
sh_exec_builtin(int argc, char **argv)
{
	int i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (!ft_strcmp(argv[0], builtin_names[i]))
			return ((*builtin_func[i])(argc, argv));
		i++;
	}
	return (-1);
}

int
sh_exec(int argc, char **argv)
{
	if (!argv[0])
		return (1);
	if (sh_exec_builtin(argc, argv) == -1)
		return (1);
	return (sh_exec_file(argc, argv));
}
