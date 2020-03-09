/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 21:20:21 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/03/09 21:20:21 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>

int	err_norme(const char *s)
{
	ufputs(FT_STDERR, "minishell: command not found: ");
	ufputsn(FT_STDERR, s);
	return (1);
}
