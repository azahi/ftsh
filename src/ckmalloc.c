/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ckmalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdeathlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:48:14 by jdeathlo          #+#    #+#             */
/*   Updated: 2020/06/15 16:30:35 by jdeathlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft_stdlib.h>
#include <uio.h>

void	*ckmalloc(size_t size)
{
	void	*ptr;

	ptr = ft_malloc(size);
	if (ptr == NULL)
	{
		ufputsn(STDERR_FILENO, "error: ckmalloc: malloc failed");
		exit(ENOMEM);
	}
	return (ptr);
}

void	*ckcalloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (ptr == NULL)
	{
		ufputsn(STDERR_FILENO, "error: ckcalloc: calloc failed");
		exit(ENOMEM);
	}
	return (ptr);
}

void	*ckrealloc(void *ptr, size_t size)
{
	void	*nptr;

	nptr = ft_realloc(ptr, size);
	if (nptr == NULL)
	{
		ufputsn(STDERR_FILENO, "error: ckrealloc: realloc failed");
		exit(ENOMEM);
	}
	return (nptr);
}

void	ckfree(void *ptr)
{
	if (ptr != NULL)
		ft_free(ptr);
}
