#include <ft_stdlib.h>
#include <ft_string.h>

#ifdef DEBUG
#include <stdio.h>
#endif /* !DEBUG */

#include "env.h"
#include "exec.h"
#include "gl.h"
#include "minishell.h"
#include "prompt.h"

/**
 * Splits input into arguments.
 *
 * TODO We are hard splitting every white space that we encounter. This will
 * surely break the possibility of using escape sequences like "foo\ bar" and
 * etc.
 */
char **
sh_split(char *line, int *linec)
{
	int bufsize = 1;
	char **tokens = malloc(sizeof (*tokens) * bufsize);
	char *token = ft_strtok(line, TOK_DELIM);
	int i = 0;
	while (token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 1;
			if (!(tokens = realloc(tokens, sizeof (*tokens) * bufsize)))
				exit(1);
		}
		token = ft_strtok(NULL, TOK_DELIM);
	}
	tokens[i] = NULL;
	*linec = i;
#ifdef DEBUG
	fprintf(stderr, "DEBUG: sh_split():");
	for (int j = 0; j <= i; j++)
		fprintf(stderr, " [%d] = \"%s\"", j, tokens[j]);
	fprintf(stderr, " (linec = %d)\n", *linec);
#endif /* !DEBUG */
	return (tokens);
}

/**
 * Reads a line from input.
 */
static char *
sh_getline(void)
{
	char *line = NULL;
	if (gl(0, &line) != 1)
		return (NULL);
	return (line);
}

int
main(void)
{
	lenv_init();
	while (1)
	{
		prompt();
		char *line = sh_getline();
		if (!line)
		{
			lenv_deinit();
			return (1);
		}
		int lc;
		char **lv = sh_split(line, &lc);
		if (!lv)
		{
			free(line);
			lenv_deinit();
			return (1);
		}
		int status = sh_exec(lc, lv);
		free(lv);
		free(line);
		if (status == -10)
		{
			lenv_deinit();
			return (0);
		}
	}
}
