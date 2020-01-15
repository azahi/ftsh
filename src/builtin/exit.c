#include <stdio.h>
#include <stdlib.h>

int
builtin_exit(int argc, char **argv)
{
	puts("Bye.\n");
	sh_exit(EXIT_SUCCESS);
}
