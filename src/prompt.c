#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <unistd.h>

#include "prompt.h"

/**
 * If HOME envvar is found at the beginning of the CWD we replace it with
 * '~'
 *
 * @param	cwd		Current working directory
 */
static char *
shorten_cwd(char *cwd)
{
	char *res;
	char *home;
	int home_len;
	int cwd_len;
	int res_len;

	home = getenv("HOME"); // FIXME Replace
	if (!strcmp(cwd, home))
	{
		return ("~");
	}
	else if (!strncmp(cwd, home, (home_len = strlen(home))))
	{
		cwd_len = strlen(cwd);
		res_len = cwd_len - home_len ;
		if (!(res = malloc(sizeof (*res) * (res_len + 1))))
		{
			// TODO Clean exit
			return (NULL);
		}
		*res = '~';
		memcpy(res + 1, cwd + home_len, res_len + 1);
		return (res);
	}
	else
		return (NULL);
}


void
prompt(void)
{
	char *cwd;
	char buf[PROMPT_BUF_SIZE + 1];
	char *short_cwd;

	cwd = getcwd(buf, PROMPT_BUF_SIZE); // TODO Check if this is allowed
	short_cwd = shorten_cwd(cwd);
	uputs(short_cwd);
	uputs(" $ ");
}
