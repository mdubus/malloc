/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:05:52 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 16:32:20 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	put_rest_in_free_list(t_header *best_fit, size_t size,
		t_header **current_arena)
{
	t_header	*rest;
	t_header	*tmp;
	size_t		aligned_size;

	tmp = *current_arena;
	aligned_size = size;
	if (aligned_size % sizeof(long) != 0)
		aligned_size = aligned_size + (sizeof(long) -
				aligned_size % sizeof(long));
	rest = (void*)best_fit + aligned_size;
	rest->size = best_fit->size - aligned_size;
	if ((*current_arena)->next == NULL)
	{
		*current_arena = rest;
		(*current_arena)->next = NULL;
	}
	else
		put_block_in_list(&tmp, &rest);
}

void	put_block_in_used_list(t_header *best_fit, size_t size)
{
	t_header	*tmp;
	size_t		aligned_size;

	aligned_size = size;
	if (aligned_size % sizeof(long) != 0)
		aligned_size = aligned_size + (sizeof(long) -
		aligned_size % sizeof(long));
	tmp = (void*)arena.used;
	best_fit->size = aligned_size - sizeof(t_header);
	if (arena.used == NULL)
	{
		arena.used = best_fit;
		arena.used->next = NULL;
	}
	else
		put_block_in_list(&tmp, &best_fit);
}

void	split_block(t_header **current_arena, t_header *best_fit, size_t size)
{
	size_t	rest_size;

	rest_size = best_fit->size - size;
	if (rest_size > 0)
		put_rest_in_free_list(best_fit, size, current_arena);
	put_block_in_used_list(best_fit, size);
}
