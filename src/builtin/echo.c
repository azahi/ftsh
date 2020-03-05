#include <ft.h>
#include <ft_string.h>
#include <ft_unistd.h>

#define BUILTIN_ECHO_OPTS "n"

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
			ufputs(FT_STDOUT, *argv);
			ufputc(FT_STDOUT, ' ');
			argv++;
		}
	}
	if (!nonl)
		ufputc(FT_STDOUT, '\n');
	return (0);
}
