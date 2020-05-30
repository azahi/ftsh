/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 12:46:11 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/30 23:47:47 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <errno.h>
#include <ft_stdlib.h>
#include <ft_string.h>

#include "split.h"

#define MINISHELL_INPUT_DELIMITERS "\t\n\v\f\r "


static char	**sh_split_env(int i, char *tok, char **argv)
{
	char	*expand;
	char	*expanded;
	size_t	el;
	size_t	etl;

	// TODO Fix cases for "$HOME/src"
	expand = ft_strchr(tok, '$');
	if (expand)
	{
		expand++;
		etl = expand - tok - 1;
		expanded = ft_getenv(expand);
		if (expanded)
		{
			el = ft_strlen(expanded);
			argv[i] = ft_malloc(sizeof(*argv) * (el + etl));
			ft_memcpy(argv[i], tok, etl);
			ft_memcpy(argv[i] + etl, expanded, el);
			argv[i][el + etl] = '\0';
		}
		else if (!(argv[i] = ft_strndup(tok, etl)))
			exit(ENOMEM);
	}
	else if (!(argv[i] = ft_strdup(tok)))
		exit(ENOMEM);
	return (argv);
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

static char	**expand_argv(char **argv, int i) // TODO This shit.
{
	if (!(argv = ft_realloc(argv, sizeof(*argv) * (i + 1))))
		exit(ENOMEM);
	return (argv);
}

char		**sh_split(char *line, int *argc)
{
	char	**argv;
	char	*tok;
	int		i;

	if (!(argv = ft_malloc(sizeof(*argv))))
		exit(ENOMEM);
	tok = ft_strtok(line, MINISHELL_INPUT_DELIMITERS);
	i = 0;
	while (tok)
	{
		argv = sh_split_env(i, tok, argv); // TODO Make this look better.
		argv[i] = sh_split_home(argv[i]);
		i++; // This is just can't comprehend.
		argv = expand_argv(argv, i);
		tok = ft_strtok(NULL, MINISHELL_INPUT_DELIMITERS);
	}
	argv[i] = NULL;
	*argc = i;
	return (argv);
}
