#include <ft.h>

#include "../env.h"

int
builtin_env(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	char **env = g_env;

	while(*env)
	{
		uputsn(*env);
		env++;
	}
	return (1);
}
