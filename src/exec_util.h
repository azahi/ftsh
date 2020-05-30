/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 21:47:11 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/30 21:53:25 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTIL_H
# define EXEC_UTIL_H

int	can_exec(char *a);
int	is_file(char *a);
int	sh_exec_builtin(int a, char **b);
int	sh_exec_file_errnotfound(const char a[]);

#endif
