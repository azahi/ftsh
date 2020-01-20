#include <stdio.h>

int
builtin_echo(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	puts("Not implemented.\n");
	return (1);
}
