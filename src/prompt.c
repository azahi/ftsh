#include <ft.h>
#include <ft_string.h>
#include <unistd.h>

#include "env.h"
#include "prompt.h"

/**
 * Display a prompt message.
 */
void
prompt(void)
{
	char buf[PROMPT_BUF_SIZE + 1];
	char *cwd = getcwd(buf, PROMPT_BUF_SIZE);
	char *home = lenv_getenv("HOME");
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
