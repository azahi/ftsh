#include <ft.h>
#include <ft_stdio.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <signal.h>

#ifdef DEBUG
# include <stdio.h>
#endif /* !DEBUG */

#include "env.h"
#include "exec.h"
#include "prompt.h"

#define MINISHELL_INPUT_BUFSIZE 8
#define MINISHELL_INPUT_DELIMITERS "\t\n\v\f\r "

/**
 * Splits input into arguments.
 */
static char **
sh_split(char *line, int *linec)
{
	int bufsize = MINISHELL_INPUT_BUFSIZE;
	char **tokens = malloc(sizeof (*tokens) * bufsize);
	char *token = ft_strtok(line, MINISHELL_INPUT_DELIMITERS);
	int i = 0;
	while (token)
	{
		/**
		 * Environment variable expansion.
		 */
		char *expand = ft_strchr(token, '$');
		if (expand)
		{
			expand++;
			size_t etl = expand - token - 1;
			char *expanded = lenv_getenv(expand);
			if (expanded)
			{
				size_t el = ft_strlen(expanded);
				tokens[i] = malloc(sizeof (*tokens) * (el + etl));
				ft_memcpy(tokens[i], token, etl);
				ft_memcpy(tokens[i] + etl, expanded, el);
				tokens[i][el + etl] = '\0';
			}
			else
				tokens[i] = ft_strndup(token, etl);
		}
		else
			tokens[i] = ft_strdup(token);

		/**
		 * '~' expansion.
		 */
		if (*tokens[i] == '~')
		{
			char *home_expand = lenv_getenv("HOME");
			size_t hl = ft_strlen(home_expand);
			size_t tl = ft_strlen(tokens[i]);
			char *tmp = malloc(sizeof (*tmp) * (hl + tl - 1));
			ft_memcpy(tmp, home_expand, hl);
			ft_memcpy(tmp + hl, tokens[i] + 1, tl - 1);
			tmp[hl + tl] = '\0';
			free(tokens[i]);
			tokens[i] = tmp;
		}

		i++;
		if (i >= bufsize)
		{
			bufsize += MINISHELL_INPUT_BUFSIZE;
			char **t;
			if (!(t = malloc(sizeof (*t) * bufsize)))
				exit(EXIT_FAILURE);
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

static void
sigint_shell()
{
	ufputc(FT_STDOUT, '\n');
	prompt();
}

static void	free_lv(char ***lv)
{
	char **lvp;

	lvp = *lv;
	while (*lvp)
	{
		free(*lvp);
		lvp++;
	}
	free(*lv);
}

int			main(int argc, char **argv)
{
	char	*line;
	int		lc;
	char	**lv;
	int		status;

	lenv_setenv("SHELL", argv[0], 1);
	while (1)
	{
		signal(SIGINT, sigint_shell);
		prompt();
		if (ugetline(FT_STDIN, &line) != 1)
		{
			ufputc(FT_STDOUT, '\n');
			exit(EXIT_FAILURE);
		}
		lv = sh_split(line, &lc);
		free(line);
		if (!lv)
			exit(EXIT_FAILURE);
		status = sh_exec(lc, lv);
		free_lv(&lv);
		if (status == -10)
			exit(EXIT_SUCCESS);
	}
}
