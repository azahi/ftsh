#include "exec.h"
#include "builtin/builtin.h"

/**
 * Executes from PATH.
 */
static int
exec_path(char **argv)
{
	pid_t pid, wpid;
	int wstatus;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1) // TODO Switch to execve
			perror(NULL);
		exit(errno);
	}
	else if (pid < 0)
	{
		perror(NULL);
	}
	else
	{
		do
			wpid = waitpid(pid, &wstatus, WUNTRACED); // POSIX magic.
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
	return (1);
}

/**
 * Executes a builtin if argv[0] corresponds to an element in builtin array.
 */
int
sh_exec(int argc, char **argv)
{
	if (!argv[0])
		return (1);

	for (int i = 0; i < BUILTIN_COUNT; i++)
	{
		if (strcmp(argv[0], builtin_names[i]) == 0)
			return ((*builtin_func[i])(argc, argv));
	}

	return (sh_execvp(argv));
}
