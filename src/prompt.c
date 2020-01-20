#include "prompt.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ft.h>

static char
*shorten_cwd(char *cwd)
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
		if (!(res = malloc(sizeof (*res) * res_len)))
		{
			// TODO Clean exit
			return (NULL);
		}
		memcpy(res, cwd + home_len, res_len);
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

	cwd = getcwd(buf, PROMPT_BUF_SIZE);
	short_cwd = shorten_cwd(cwd);
	uputs(short_cwd);
	uputs(" $ ");
}
