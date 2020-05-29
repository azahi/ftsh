/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 12:46:11 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/29 13:41:05 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <errno.h>
#include <ft_stdlib.h>
#include <ft_string.h>

#include <stdio.h>

#include "split.h"

#define MINISHELL_INPUT_BUFSIZE 8
#define MINISHELL_INPUT_DELIMITERS "\t\n\v\f\r "

/*
** TODO Fix cases for "$HOME/src"
*/

static char	**sh_split_env(int i, char *token, char **tokens)
{
	char	*expand;
	char	*expanded;
	size_t	el;
	size_t	etl;

	expand = ft_strchr(token, '$');
	if (expand)
	{
		expand++;
		etl = expand - token - 1;
		expanded = ft_getenv(expand);
		if (expanded)
		{
			el = ft_strlen(expanded);
			tokens[i] = ft_malloc(sizeof(*tokens) * (el + etl));
			ft_memcpy(tokens[i], token, etl);
			ft_memcpy(tokens[i] + etl, expanded, el);
			tokens[i][el + etl] = '\0';
		}
		else if (!(tokens[i] = ft_strndup(token, etl)))
			exit(ENOMEM);
	}
	else if (!(tokens[i] = ft_strdup(token)))
		exit(ENOMEM);
	return (tokens);
}

static char	*sh_split_home(char *tok)
{
	char	*var;
	char	*tmp;
	size_t	varlen;
	size_t	toklen;

	if (*tok == '~')
	{
		var = ft_getenv("HOME");
		varlen = ft_strlen(var);
		toklen = ft_strlen(tok);
		if (!(tmp = ft_malloc(sizeof(*tmp) * (varlen + toklen))))
			exit(ENOMEM);
		ft_memcpy(tmp, var, varlen);
		ft_memcpy(tmp + varlen, tok + 1, toklen);
		tmp[varlen + toklen - 1] = '\0';
		ft_free(tok);
		tok = tmp;
	}
	return (tok);
}

char		**sh_split(char *line, int *linec)
{
	char	**tmp;
	char	**tokens;
	char	*token;
	int		bufsize;
	int		i;
	int		j;

	bufsize = MINISHELL_INPUT_BUFSIZE;
	if (!(tokens = ft_malloc(sizeof(*tokens) * bufsize)))
		exit(ENOMEM);
	token = ft_strtok(line, MINISHELL_INPUT_DELIMITERS);
	i = 0;
	while (token)
	{
		tokens = sh_split_env(i, token, tokens);
		tokens[i] = sh_split_home(tokens[i]);
		i++;
		if (i >= bufsize)
		{
			bufsize += MINISHELL_INPUT_BUFSIZE;
			if (!(tmp = ft_malloc(sizeof(*tmp) * bufsize)))
				exit(ENOMEM);
			for (j = 0; j < bufsize - MINISHELL_INPUT_BUFSIZE; j++)
				tmp[j] = tokens[j];
			ft_free(tokens);
			tokens = tmp;
		}
		token = ft_strtok(NULL, MINISHELL_INPUT_DELIMITERS);
	}
	tokens[i] = NULL;
	*linec = i;

	return (tokens);
}
