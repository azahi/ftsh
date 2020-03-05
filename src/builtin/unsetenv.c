#include <ft.h>

#include "../env.h"

int
builtin_unsetenv(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	lenv_unsetenv(argv[1]);

	return (0);
}
