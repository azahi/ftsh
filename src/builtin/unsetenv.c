/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:39:40 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/07 18:39:48 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>

#include "../env.h"

int	builtin_unsetenv(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	lenv_unsetenv(argv[1]);
	return (0);
}
