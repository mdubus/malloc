/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:09:06 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 09:47:01 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	init_new_block(t_header *arena, size_t size)
{
	arena->next = NULL;
	arena->size = size - sizeof(t_header);
}

void	*get_new_arena(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	init_new_block(ptr, size);
	return (ptr);
}
