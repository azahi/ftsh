#include <ft.h>
#include <ft_string.h>

int
builtin_echo(int argc, char **argv)
{
	(void)argc;
	int nonl = 0;
	if (!ft_strcmp(argv[1], "-n"))
		nonl = 1;
	while (*argv)
	{
		uputs(*argv);
		uputc(' ');
		argv++;
	}
	if (nonl)
		uputc('\n');
	return (0);
}
