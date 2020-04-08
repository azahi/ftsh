#include <uio.h>

extern char **environ;

int
builtin_env(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char **env = environ;
	while(*env)
	{
		uputsn(*env);
		env++;
	}
	return (0);
}
