#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <uio.h>

int	builtin_setenv(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	ft_setenv(argv[1], argv[2], 1);
	return (0);
}
