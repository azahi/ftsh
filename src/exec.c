#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
		exit(0);
	}
	else if (pid < 0)
	{
		uputs("minishell: failed to create a new process.\n");
		return (1);
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
	struct stat st;
	if (!stat(file, &st))
		if (st.st_mode & S_IXUSR)
			return (1);
	return (0);
}

static int
sh_exec_file(char **argv) // TODO Adhere to subject
{
	if (strchr(argv[0], '/') && can_exec(argv[0]))
		return (exec_proc(argv[0], argv));

	size_t k = strnlen(argv[0], NAME_MAX + 1);
	if (k > NAME_MAX)
		return (1);

	char *path = lenv_getenv("PATH");
	if (!path)
		path = "/usr/local/bin:/usr/bin:/bin";
	size_t l = strnlen(path, PATH_MAX - 1) + 1;

	char *file = malloc(sizeof(*file) * l);
	*file = '\0';
	char *elem = strtok(path, ":");
	strcat(file, elem);
	strcat(file, "/");
	strcat(file, argv[0]);
	if (can_exec(file))
		return (exec_proc(file, argv));
	while (elem)
	{
		*file = '\0';
		elem = strtok(NULL, ":");
		strcat(file, elem);
		strcat(file, "/");
		strcat(file, argv[0]);
		if (can_exec(file))
			return (exec_proc(file, argv));
	}
	free(file);
	uputs("minishell: command not found.\n");
	return (1);
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
	int ret;
	if ((ret = sh_exec_builtin(argc, argv)) != -1)
		return (ret);
	return (sh_exec_file(argv));
}
