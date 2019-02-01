/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:53:57 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 11:53:00 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	put_block_in_list(t_header **tmp, t_header **next_block)
{
	if ((*tmp)->next == NULL)
	{
		(*tmp)->next = *next_block;
		(*tmp)->next->next = NULL;
	}
	else
	{
		(*next_block)->next = (*tmp)->next;
		(*tmp)->next = *next_block;
	}
}

void	put_rest_in_free_list(t_header *best_fit, size_t size, t_header **current_arena)
{
	t_header	*rest;
	t_header	*tmp;
	size_t		aligned_size;

	tmp = *current_arena;
	aligned_size = size;
	if (aligned_size % sizeof(long) != 0)
		aligned_size = aligned_size + (sizeof(long) - aligned_size % sizeof(long));
	rest = (void*)best_fit + aligned_size;
	rest->size = best_fit->size - size;

	if ((*current_arena)->next == NULL)
	{
		*current_arena = rest;
		(*current_arena)->next = NULL;
	}
	else
	{
		while (tmp && tmp->next != NULL && rest < tmp->next)
			tmp = tmp->next;
		put_block_in_list(&tmp, &rest);
	}
}

void	put_block_in_used_list(t_header *best_fit, size_t size)
{
	size_t		aligned_size;
	t_header	*tmp;

	aligned_size = size;
	tmp = (void*)arena.used;
	if (aligned_size % sizeof(long) != 0)
		aligned_size = aligned_size + (sizeof(long) - aligned_size % sizeof(long));
	best_fit->size = size - sizeof(t_header);

	if (arena.used == NULL)
	{
		arena.used = best_fit;
		arena.used->next = NULL;
	}
	else
	{
		while (tmp && tmp->next != NULL && best_fit > tmp->next)
			tmp = tmp->next;
		put_block_in_list(&tmp, &best_fit);
	}
}

void	split_block(t_header **current_arena, t_header *best_fit, size_t size)
{
	// EXTRAIT LE MORCEAU DE PRIS ET ON LINK LES FREE ENTRE EUX
	// A-t-on la place dans le morceau restant pour stocker un header ?
	// Si oui, on cree un nouveau maillon (ci-dessous)
	// Si non, on defragmente si on peut.
	// Si pas de defrag, on le laisse avec le maillon used

	put_rest_in_free_list(best_fit, size, current_arena);
	put_block_in_used_list(best_fit, size);
}

void	*ft_malloc(size_t size)
{
	size_t		max_tiny;
	size_t		max_small;
	t_header	*best_fit;

	if (size <= 0)
		return NULL;
	best_fit = NULL;
	max_tiny = (size_t)MAX_TINY * getpagesize();
	max_small = (size_t)MAX_SMALL * getpagesize();

	if ((void*)arena.tiny == NULL)
		arena.tiny = get_new_arena(max_tiny);
	if ((void*)arena.small == NULL)
		arena.small = get_new_arena(max_small);
	if (arena.tiny == NULL || arena.small == NULL)
		return NULL;

	if (size + sizeof(t_header) <= max_tiny)
	{
		best_fit = search_best_fit(arena.tiny, size + sizeof(t_header));
		if (best_fit == NULL)
		{
			// Get new arena and put it in the free list, ordered by addresses
			best_fit = get_new_arena(max_tiny);
			return best_fit;
		}
		else
		{
			split_block(&arena.tiny, best_fit, size + sizeof(t_header));
			return best_fit + sizeof(t_header);
		}
	}
	return (NULL);
}
