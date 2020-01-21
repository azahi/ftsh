#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <unistd.h>

#include "env.h"
#include "minishell.h"
#include "prompt.h"

/**
 * If $HOME is found at the beginning of the CWD we replace it with '~'
 *
 * @param	cwd		Current working directory
 */
static char *
shorten_cwd(char *cwd)
{
	char *home;
	char *res;
	int cwd_len;
	int home_len;
	int res_len;

	home = lenv_getenv("HOME"); // FIXME Replace
	if (!strcmp(cwd, home))
		return ("~");
	else if (!strncmp(cwd, home, (home_len = strlen(home))))
	{
		cwd_len = strlen(cwd);
		res_len = cwd_len - home_len ;
		/**
		 * TODO Rework this so we don't have to dynamically allocate the
		 * resulting string. Something like what we have done with
		 * lenv_getenv() will suffice, I suppose.
		 */
		if (!(res = malloc(sizeof (*res) * (res_len + 1))))
			clean_exit(1);
		*res = '~';
		memcpy(res + 1, cwd + home_len, res_len + 1);
		return (res);
	}
	else
		return (NULL);
}

/**
 * Display a prompt message with neat features
 */
void
prompt(void)
{
	char *cwd;
	char *short_cwd;
	char buf[PROMPT_BUF_SIZE + 1];

	cwd = getcwd(buf, PROMPT_BUF_SIZE);
	short_cwd = shorten_cwd(cwd);

	uputs(short_cwd);
	uputs(" $ ");
}
