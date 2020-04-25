#include <uio.h>

int
builtin_env(int argc, char **argv)
{
	extern char	**environ;

	(void)argc;
	(void)argv;
	char **e = environ;
	while(*e)
	{
		uputsn(*e);
		e++;
	}
	return (0);
}
