#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <ft_string.h>
#include <uio.h>

#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif

#include "prompt.h"

#define HOSTNAME_SIZE 64

/**
 * Display a prompt message.
 */
void
prompt(void)
{
	uputs(ft_getenv("USER"));
	char host[HOSTNAME_SIZE] = { 0 };
	if (!gethostname(host, HOSTNAME_SIZE))
	{
		uputc('@');
		uputs(host);
	}
	uputc(':');
	char buf[PATH_MAX + 1];
	char *cwd = getcwd(buf, PATH_MAX);
	char *home = ft_getenv("HOME");
	size_t home_l = ft_strlen(home);
	if (!ft_strncmp(cwd, home, home_l))
	{
		uputc('~');
		uputs(cwd + home_l);
	}
	else
		uputs(cwd);
	uputs(" $ ");
}
