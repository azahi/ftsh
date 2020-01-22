/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:24:31 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/01/22 14:24:47 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

/*
** Linux has a maximum filename length of 255 characters for most filesystems
** (including EXT4), and a maximum path of 4096 characters.
*/

# define PROMPT_BUF_SIZE 4096

void prompt(void);

#endif
