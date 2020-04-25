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
	char *oldpwd = ft_getenv("OLDPWD");
	if (!oldpwd)
		oldpwd = ft_strdup(buf);
	if (!target)
		target = ft_getenv("HOME");
	else if (!ft_strcmp(target, "-"))
	{
		ufputsn(STDERR_FILENO, oldpwd);
		target = oldpwd;
	}
	if (chdir(target) == -1)
	{
		ufputs(STDERR_FILENO, "cd: error: ");
		ufputsn(STDERR_FILENO, target);
		return (1);
	}
	ft_setenv("OLDPWD", buf, 1);
	getcwd(buf, sizeof (buf));
	ft_setenv("PWD", buf, 1);
	return (0);
}
