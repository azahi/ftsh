/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ckmalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:46:24 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/06/15 16:30:30 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CKMALLOC_H
# define CKMALLOC_H

# include <stddef.h>

void	*ckcalloc(size_t a, size_t b);
void	*ckmalloc(size_t a);
void	*ckrealloc(void *a, size_t b);
void	ckfree(void *a);

#endif
