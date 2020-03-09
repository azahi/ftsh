/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:30:14 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/09 14:24:47 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>

#include "../env.h"

int	builtin_env(int argc, char **argv)
{
	char **env;

	(void)argc;
	(void)argv;
	env = environ;
	while (*env)
	{
		ufputsn(FT_STDOUT, *env);
		env++;
	}
	return (0);
}
