#include <ft.h>

#include "../env.h"

int
builtin_setenv(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	lenv_setenv(argv[1], argv[2], 1);

	return (0);
}
