#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <uio.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

#include "prompt.h"

#define HOSTNAME_SIZE 64

/**
 * Display a prompt message.
 */
void	prompt(void)
{
	char	*cwd;
	char	*home;
	char	buf[PATH_MAX + 1];
	char	host[HOSTNAME_SIZE];
	size_t	home_l;

	uputs(ft_getenv("USER"));
	if (!gethostname(host, HOSTNAME_SIZE))
	{
		uputc('@');
		uputs(host);
	}
	uputc(':');
	cwd = getcwd(buf, PATH_MAX);
	home = ft_getenv("HOME");
	home_l = ft_strlen(home);
	if (!ft_strncmp(cwd, home, home_l))
	{
		uputc('~');
		uputs(cwd + home_l);
	}
	else
		uputs(cwd);
	uputs(" $ ");
}
