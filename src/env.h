/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:42:55 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/07 18:46:24 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char	**g_env;
char	*lenv_getenv(const char *name);
int		lenv_setenv(char *key, char *val, int overwrite);
int		lenv_unsetenv(char *name);
void	lenv_init(void);
void	lenv_deinit(void);

#endif
