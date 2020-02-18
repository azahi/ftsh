#include <ft_stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../env.h"

int
builtin_exit(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	/*
	lenv_deinit();
	exit(EXIT_SUCCESS);
	*/

	return (-10);
}
