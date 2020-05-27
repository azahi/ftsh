#include <uio.h>

int	builtin_env(int argc, char **argv)
{
	extern char	**environ;
	char		**e;

	(void)argc;
	(void)argv;
	e = environ;
	while (*e)
	{
		uputsn(*e);
		e++;
	}
	return (0);
}
