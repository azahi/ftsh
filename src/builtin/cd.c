/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pparalax <pparalax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:45:16 by pparalax          #+#    #+#             */
/*   Updated: 2020/03/07 18:18:32 by pparalax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_unistd.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

#include "../env.h"

static int	builtin_cd_norme(char *target)
{
	ufputs(FT_STDERR, "cd: error: ");
	ufputsn(FT_STDERR, target);
	return (1);
}

int			builtin_cd(int argc, char **argv)
{
	char		*target;
	char		buf[PATH_MAX];
	static char	*prev_dir;

	target = argv[1];
	(void)argc;
	if (!getcwd(buf, sizeof(buf)))
		return (builtin_cd_norme(target));
	prev_dir = (!prev_dir) ? ft_strdup(buf) : prev_dir;
	if (argv[1] && !ft_strcmp(target, "-"))
	{
		ufputsn(FT_STDERR, prev_dir);
		target = prev_dir;
	}
	target = (!target) ? lenv_getenv("HOME") : target;
	if (chdir(target) == -1)
		return (builtin_cd_norme(target));
	free(prev_dir);
	prev_dir = ft_strdup(buf);
	return (0);
}
