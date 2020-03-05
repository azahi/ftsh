#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>

#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif

#include "../env.h"

int
builtin_cd(int argc, char **argv)
{
	(void)argc;

	char *target = argv[1];
	char buf[PATH_MAX];
	if (!getcwd(buf, sizeof (buf)))
	{
		uputs("cd: error: ");
		uputsn(target);
		return (1);
	}
	static char *prev_dir;
	if (!prev_dir)
		prev_dir = ft_strdup(buf);
	if (argv[1])
	{
		if (!ft_strcmp(target, "-"))
		{
			ufputsn(FT_STDERR, prev_dir);
			target = prev_dir;
		}
	}
	if (!target)
		target = lenv_getenv("HOME");
	if (chdir(target) == -1)
	{
		ufputs(FT_STDERR, "cd: error: ");
		ufputsn(FT_STDERR, target);
		return (1);
	}
	free(prev_dir);
	prev_dir = ft_strdup(buf);
	return (0);
}
