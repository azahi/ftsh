#include <ft_stdlib.h>
#include <ft_string.h>
#include <stdio.h>

#include "env.h"
#include "exec.h"
#include "minishell.h"
#include "prompt.h"

void
clean_exit(int code)
{
	lenv_deinit();
	exit(code);
}

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
	char **tokens;
	char *token;
	int bufsize = TOK_BUFSIZE;
	int i = 0;

	if (!(tokens = malloc(sizeof (**tokens) * bufsize)))
	{
		clean_exit(1);
	}

	token = strtok(line, TOK_DELIM); // FIXME Replace
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
				clean_exit(1);
			}
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
	char	**lv;
	char	*line;
	int		lc;

	lenv_init();
	while (1)
	{
		prompt();
		line = sh_getline();
		lv = sh_split(line, &lc);
		sh_exec(lc, lv);

		free(line);
		free(lv);
	}
	clean_exit(EXIT_SUCCESS);
}
