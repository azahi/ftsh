#include <ft.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../env.h"

int
builtin_setenv(int argc, char **argv)
{
	(void)argc;

	if (!argv[1])
		return (1);
	if (!argv[2])
		lenv_set(argv[1], NULL);
	lenv_set(argv[1], argv[2]);

	return (0);
}
