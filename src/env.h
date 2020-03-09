/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:42:55 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 21:16:41 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define EXTERN_CHAR_ENVIRON extern char **environ

EXTERN_CHAR_ENVIRON;

char	*lenv_getenv(const char *name);

int		lenv_setenv(const char *key, const char *val, int overwrite);
int		lenv_unsetenv(const char *name);

void	env_rm_add(char *old, char *new);

#endif
