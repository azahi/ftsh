#include <ft_string.h>
#include <uio.h>

int
builtin_echo(int argc, char **argv)
{
	(void)argc;
	int nonl = 0;
	if (argv[1])
	{
		argv++;
		if (!ft_strcmp(*argv, "-n"))
		{
			nonl = 1;
			argv++;
		}
		while (*argv)
		{
			uputs(*argv);
			if (*(argv + 1))
				uputc(' ');
			argv++;
		}
	}
	if (!nonl)
		uputc('\n');
	return (0);
}
