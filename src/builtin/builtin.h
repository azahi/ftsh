/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:15:10 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/07 17:31:55 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define BUILTIN_COUNT 6

int			builtin_cd(int argc, char **argv);
int			builtin_echo(int argc, char **argv);
int			builtin_env(int argc, char **argv);
int			builtin_exit(int argc, char **argv);
int			builtin_setenv(int argc, char **argv);
int			builtin_unsetenv(int argc, char **argv);

const char	*g_builtin_names[] = {
	"cd",
	"echo",
	"env",
	"exit",
	"setenv",
	"unsetenv"
};

int			(*g_builtin_func[])(int, char **) = {
	&builtin_cd,
	&builtin_echo,
	&builtin_env,
	&builtin_exit,
	&builtin_setenv,
	&builtin_unsetenv
};

#endif
