#include <stdlib.h>

#include "minishell.h"
#include "env.h"

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
	int bufsize = TOK_BUFSIZE, i = 0;
	char **tokens, *token;

	// FIXME Numerical operations are kinda useless on "constant" malloc().
	if (!(tokens = malloc(sizeof (**tokens) * bufsize)))
	{
		exit(1);
	}

	token = strtok(line, TOK_DELIM);
	while (token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			if (!(tokens = realloc(tokens, sizeof (**tokens) * bufsize)))
			{
				// FIXME Iteratively clean tokens on failure.
				exit(1);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[i] = NULL;
	*linec = i;
	return (tokens);
}

/**
 * Reads a line from input.
 */
static char *
sh_getline(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin); // FIXME Not allowed
	return (line);
}

int
main(int argc, char **argv)
{
	char	**lv;
	char	*line;
	int		i;
	int		lc;

	lenv_init();
	while (1)
	{
		printf("> ");
		line = sh_getline();
		lv = sh_split(line, &lc);
		sh_exec(lc, lv);

		free(line);
		free(lv);
	}
	exit(EXIT_SUCCESS);
}
