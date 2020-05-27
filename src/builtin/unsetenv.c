#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <uio.h>

int	builtin_unsetenv(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	ft_unsetenv(argv[1]);
	return (0);
}
