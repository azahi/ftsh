#include <ft_stdlib.h>

int
builtin_exit(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	exit(EXIT_SUCCESS);

	return (0);
}
