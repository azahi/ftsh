#include <ft.h>
#include <ft_string.h>
#include <limits.h>
#include <unistd.h>

#include "env.h"
#include "prompt.h"

#define HOSTNAME_SIZE 64

/**
 * Display a prompt message.
 */
#ifdef DEBUG
void
prompt(void)
{
	ufputs(FT_STDOUT, "minishell_debug> ");
}
#else
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
#endif /* !DEBUG */
