/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:42:55 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 14:22:29 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENV_H__
#define __ENV_H__

#define ENV extern char **environ

ENV;

char *lenv_getenv(const char *);

int lenv_setenv(const char *, const char *, int);
int lenv_unsetenv(const char *);

#endif /* !__ENV_H__ */
