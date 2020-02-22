#include <ft_stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

int
builtin_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	return (-10);
}
