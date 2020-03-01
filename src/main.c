#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <signal.h>

#ifdef DEBUG
#include <stdio.h>
#endif /* !DEBUG */

#include "env.h"
#include "exec.h"
#include "prompt.h"

#define MINISHELL_INPUT_BUFSIZE 8
#define MINISHELL_INPUT_DELIMITERS "\t\n\v\f\r "

/**
 * Splits input into arguments.
 *
 * TODO We are hard splitting every white space that we encounter. This will
 * surely break the possibility of using escape sequences like "foo\ bar" and
 * etc.
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
		tokens[i] = token;
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
print_version(void)
{
	ufputs(FT_STDOUT, "minishell, version 0.1\n");
	ufputs(FT_STDOUT, "Copyright (C) 2020 Azat Bahawi <azahi@teknik.io>\n");
	ufputs(FT_STDOUT,
			"License WTFPL: version 2 or later <http://www.wtfpl.net/txt/copying/>\n");
	ufputc(FT_STDOUT, '\n');
	ufputs(FT_STDOUT, "This is non-free software; ");
	ufputs(FT_STDOUT, "you are free to do whatever the fuck you want to do.\n");
	ufputs(FT_STDOUT, "There is NO FUCKS GIVEN ABOUT WARRANITY, ");
	ufputs(FT_STDOUT, "to the extent permitted by law.\n");
	ufputc(FT_STDOUT, '\n');
	ufputs(FT_STDOUT, "Written by jdeathlo and pparalax.\n");
	exit(EXIT_SUCCESS);
}

static void
print_usage(void)
{
	ufputs(FT_STDOUT, "Usage: minishell [-vh]\n");
	ufputs(FT_STDOUT, "\n\t-v\tprint version\n");
	exit(EXIT_SUCCESS);
}

int
main(int argc, char **argv)
{
	char ch;
	while ((ch = ft_getopt(argc, argv, "v")) != -1)
	{
		if (ch == 'v')
			print_version();
		else if (ch == 'h')
			print_usage();
		else
			print_usage();
	}
	argc -= g_optind;
	argv += g_optind;

	lenv_init();
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		prompt();
		char *line = NULL;
		if (ugetline(FT_STDIN, &line) != 1)
		{
			lenv_deinit();
			exit(EXIT_FAILURE);
		}
		int lc;
		char **lv = sh_split(line, &lc);
		if (!lv)
		{
			free(line);
			lenv_deinit();
			exit(EXIT_FAILURE);
		}
		int status = sh_exec(lc, lv);
		free(lv);
		free(line);
		if (status == -10)
		{
			lenv_deinit();
			exit(EXIT_SUCCESS);
		}
	}
}
