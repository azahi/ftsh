#include <ft_stdlib.h>
#include <ft_string.h>
#include <stdio.h>

#include "env.h"
#include "exec.h"
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
	int bufsize = TOK_BUFSIZE;
	char **tokens = malloc(sizeof (**tokens) * bufsize);
	char *token = strtok(line, TOK_DELIM); // FIXME Replace
	int i = 0;
	while (token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			if (!(tokens = realloc(tokens, sizeof (**tokens) * bufsize)))
				// FIXME Iteratively clean tokens on failure.
				exit(1);
		}
		token = strtok(NULL, TOK_DELIM); // FIXME Replace
	}
	tokens[i] = NULL;
	*linec = i;
	return (tokens);
}

/**
 * Reads a line from input.
 */
static char *
sh_getline(void) // TODO get_next_line
{
	char *line = NULL;
	size_t bufsize = 0;
	getline(&line, &bufsize, stdin); // FIXME Replace
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
		int lc;
		char **lv = sh_split(line, &lc);
		sh_exec(lc, lv);
	}
	exit(EXIT_SUCCESS);
}
