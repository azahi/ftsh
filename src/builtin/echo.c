#include <ft.h>
#include <ft_string.h>

int
builtin_echo(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	ufputs(FT_STDERR, "echo: not implemented.\n");

	return (0);
}
