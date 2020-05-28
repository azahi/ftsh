/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:07:10 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/05/28 11:07:11 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <ft_stdlib.h>
#include <uio.h>

int	builtin_unsetenv(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	ft_unsetenv(argv[1]);
	return (0);
}
