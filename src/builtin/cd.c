#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <uio.h>

#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif

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
			ufputsn(STDERR_FILENO, prev_dir);
			target = prev_dir;
		}
	}
	if (!target)
		target = ft_getenv("HOME");
	if (chdir(target) == -1)
	{
		ufputs(STDERR_FILENO, "cd: error: ");
		ufputsn(STDERR_FILENO, target);
		return (1);
	}
	free(prev_dir);
	prev_dir = ft_strdup(buf);
	return (0);
}
