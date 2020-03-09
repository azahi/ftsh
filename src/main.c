/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:22:14 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 20:00:34 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>
#include <ft_stdio.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <signal.h>

#include "env.h"
#include "exec.h"
#include "prompt.h"

#define MINISHELL_INPUT_BUFSIZE 8
#define MINISHELL_INPUT_DELIMITERS "\t\n\v\f\r "

static void	sh_split_tilda(char **tokens, int i)
{
	char	*home_expand;
	size_t	hl;
	size_t	tl;
	char	*tmp;

	home_expand = lenv_getenv("HOME");
	hl = ft_strlen(home_expand);
	tl = ft_strlen(tokens[i]);
	tmp = malloc(sizeof(*tmp) * (hl + tl - 1));
	ft_memcpy(tmp, home_expand, hl);
	ft_memcpy(tmp + hl, tokens[i] + 1, tl - 1);
	tmp[hl + tl - 1] = '\0';
	free(tokens[i]);
	tokens[i] = tmp;
}

static void	sh_split_dollar(char **tokens, int i, char *token)
{
	char	*expand;
	char	*expanded;
	size_t	etl;
	size_t	el;

	if ((expand = ft_strchr(token, '$')))
	{
		expand++;
		etl = expand - token - 1;
		expanded = lenv_getenv(expand);
		if (expanded)
		{
			el = ft_strlen(expanded);
			tokens[i] = malloc(sizeof(*tokens) * (el + etl));
			ft_memcpy(tokens[i], token, etl);
			ft_memcpy(tokens[i] + etl, expanded, el);
			tokens[i][el + etl] = '\0';
		}
		else
			tokens[i] = ft_strndup(token, etl);
	}
	else
		tokens[i] = ft_strdup(token);
}

static void	sh_split_bufsize(char ***tokens, int *bufsize)
{
	char	**t;
	int		j;

	*bufsize += MINISHELL_INPUT_BUFSIZE;
	if (!(t = malloc(sizeof(*t) * *bufsize)))
		exit(EXIT_FAILURE);
	j = 0;
	while (j < *bufsize - MINISHELL_INPUT_BUFSIZE)
	{
		t[j] = *tokens[j];
		j++;
	}
	free(*tokens);
	*tokens = t;
}

static char	**sh_split(char *line, int *linec)
{
	int		bufsize;
	char	**tokens;
	char	*token;
	int		i;

	bufsize = MINISHELL_INPUT_BUFSIZE;
	tokens = malloc(sizeof(*tokens) * bufsize);
	token = ft_strtok(line, MINISHELL_INPUT_DELIMITERS);
	i = 0;
	while (token)
	{
		sh_split_dollar(tokens, i, token);
		if (*tokens[i] == '~')
			sh_split_tilda(tokens, i);
		i++;
		if (i >= bufsize)
			sh_split_bufsize(&tokens, &bufsize);
		token = ft_strtok(NULL, MINISHELL_INPUT_DELIMITERS);
	}
	tokens[i] = NULL;
	*linec = i;
	return (tokens);
}

static void	sigint_shell(int sig)
{
	(void)sig;
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

	(void)argc;
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
