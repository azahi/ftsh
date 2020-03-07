/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:34:29 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/07 18:39:31 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>

#include "../env.h"

int	builtin_setenv(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	lenv_setenv(argv[1], argv[2], 1);
	return (0);
}
