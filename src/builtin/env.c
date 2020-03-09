#include <ft.h>

#include "../env.h"

int
builtin_env(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char **env = environ;
	while(*env)
	{
		ufputsn(FT_STDOUT, *env);
		env++;
	}
	return (0);
}
