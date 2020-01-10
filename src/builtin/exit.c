#include <ft_stdio.h>
#include <ft_stdlib.h>

int
builtin_exit(int argc, char **argv, int *envc, char ***envp)
{
	ft_printf("Bye.\n");
	exit(EXIT_SUCCESS);
	/* Not reachable */
}
