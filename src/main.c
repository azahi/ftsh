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
	int bufsize = MINISHELL_INPUT_BUFSIZE;
	char **tokens = malloc(sizeof (*tokens) * bufsize);
	char *token = ft_strtok(line, MINISHELL_INPUT_DELIMITERS);
	int i = 0;
	while (token)
	{
		tokens[i] = token;
		i++;
		if (i >= bufsize)
		{
			char **t;
			bufsize += MINISHELL_INPUT_BUFSIZE;
			if (!(t = malloc(sizeof (*t) * bufsize)))
				exit(1);
			for (int j = 0; j < bufsize - MINISHELL_INPUT_BUFSIZE; j++)
				t[j] = tokens[j];
			free(tokens);
			tokens = t;
		}
		token = ft_strtok(NULL, MINISHELL_INPUT_DELIMITERS);
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

int
main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	lenv_init();
	while (1)
	{
		prompt();
		char *line = NULL;
		if (gl(FT_STDOUT, &line) != 1)
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
