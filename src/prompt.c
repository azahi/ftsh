#ifdef __linux__
#define _GNU_SOURCE
#endif /* !_GNU_SOURCE */

#include <ft.h>
#include <ft_string.h>
#include <ft_unistd.h>

#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif

#include "env.h"
#include "prompt.h"

#define HOSTNAME_SIZE 64

/**
 * Display a prompt message.
 */
void
prompt(void)
{
	ufputs(FT_STDOUT, lenv_getenv("USER"));
	char host[HOSTNAME_SIZE] = { 0 };
	if (!gethostname(host, HOSTNAME_SIZE))
	{
		ufputc(FT_STDOUT, '@');
		ufputs(FT_STDOUT, host);
	}
	ufputc(FT_STDOUT, ':');
	char buf[PATH_MAX + 1];
	char *cwd = getcwd(buf, PATH_MAX);
	char *home = lenv_getenv("HOME");
	size_t home_l = ft_strlen(home);
	if (!ft_strncmp(cwd, home, home_l))
	{
		ufputc(FT_STDOUT, '~');
		ufputs(FT_STDOUT, cwd + home_l);
	}
	else
		ufputs(FT_STDOUT, cwd);
	ufputs(FT_STDOUT, " $ ");
}

#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#endif /* !_GNU_SOURCE */
