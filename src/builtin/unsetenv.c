#include <ft.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../env.h"

int
builtin_unsetenv(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	lenv_unset(argv[1]);

	return (0);
}
