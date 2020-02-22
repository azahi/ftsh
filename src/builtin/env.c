#include <ft.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../env.h"

int
builtin_env(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char **env = g_env;
	while(*env)
	{
		ufputsn(FT_STDOUT, *env);
		env++;
	}
	return (0);
}
