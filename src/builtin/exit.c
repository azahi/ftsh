#include <stdlib.h>

int
builtin_exit(int argc, char **argv)
{
	exit(EXIT_SUCCESS);
	/* Not reachable */
}
