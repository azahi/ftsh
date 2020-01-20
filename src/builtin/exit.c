#include <stdio.h>
#include <stdlib.h>

int
builtin_exit(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	puts("Bye.\n");
	exit(EXIT_SUCCESS);
	return (0);
}
