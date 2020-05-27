#pragma GCC diagnostic ignored "-Wunused-result"

#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <uio.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

int	builtin_cd(int argc, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	buf[PATH_MAX];

	(void)argc;
	target = argv[1];
	if (!getcwd(buf, sizeof buf))
	{
		uputs("cd: error: ");
		uputsn(target);
		return (1);
	}
	oldpwd = ft_getenv("OLDPWD");
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
	getcwd(buf, sizeof buf);
	ft_setenv("PWD", buf, 1);
	return (0);
}
