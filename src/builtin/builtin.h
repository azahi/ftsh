/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:00:28 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/28 11:05:13 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int			builtin_cd(int a, char **b);
int			builtin_echo(int a, char **b);
int			builtin_env(int a, char **b);
int			builtin_exit(int a, char **b);
int			builtin_setenv(int a, char **b);
int			builtin_unsetenv(int a, char **b);

const char	*g_builtin_names[] =
{
	"cd",
	"echo",
	"env",
	"exit",
	"setenv",
	"unsetenv"
};
const int	g_builtin_count = sizeof(g_builtin_names) / sizeof(char **);

int			(*g_builtin_funcs[])(int, char **) =
{
	&builtin_cd,
	&builtin_echo,
	&builtin_env,
	&builtin_exit,
	&builtin_setenv,
	&builtin_unsetenv
};

#endif
