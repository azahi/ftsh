#include <ft.h>

#include "../env.h"

int
builtin_setenv(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	lenv_set(argv[1], argv[2]);

	return (0);
}
