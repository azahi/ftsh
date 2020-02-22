#include <ft.h>
#include <ft_string.h>
#include <limits.h>
#include <unistd.h>

#include "env.h"
#include "prompt.h"

/**
 * Display a prompt message.
 */
#ifdef DEBUG
void
prompt(void)
{
	ufputs(FT_STDOUT, "> ");
}
#else
void
prompt(void)
{
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
