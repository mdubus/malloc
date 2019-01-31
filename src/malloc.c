/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:53:57 by mdubus            #+#    #+#             */
/*   Updated: 2019/01/31 16:28:54 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	split_block(t_header **current_arena, t_header *best_fit, size_t size)
{
	t_header	*rest;
	t_header	*current_used;
	size_t		aligned_size;

	aligned_size = size;
	if (aligned_size % sizeof(long) != 0)
		aligned_size = aligned_size + (sizeof(long) - aligned_size % sizeof(long));

	// EXTRAIT LE MORCEAU DE PRIS ET ON LINK LES FREE ENTRE EUX
	// A-t-on la place dans le morceau restant pour stocker un header ?
	// Si oui, on cree un nouveau maillon (ci-dessous)
	// Si non, on defragmente si on peut.
	// Si pas de defrag, on le laisse avec le maillon used
	rest = (void*)best_fit + aligned_size;
	if (best_fit->prev == NULL)
		rest->prev = NULL;
	else
	{
		best_fit->prev->next = rest;
		rest->prev = best_fit->prev;
	}
	if (best_fit->next == NULL)
		rest->next = NULL;
	else
	{
		rest->next = best_fit->next;
		best_fit->next->prev = rest;
	}
	rest->size = best_fit->size - size;
	*current_arena = rest;


	// ON LINK LE NOUVEAU MAILLON PRIS DANS USED
	// On le met tout a la fin pour le moment. Penser a les trier par adresse
	current_used = arena.used;
	while (current_used && current_used->next != NULL)
		current_used = current_used->next;
	if (current_used == NULL)
	{
		arena.used = best_fit;
		arena.used->size = size - sizeof(t_header);
		arena.used->next = NULL;
		arena.used->prev = NULL;
	}
	else
	{
		current_used->next = best_fit;
		current_used->next->prev = current_used;
		current_used->next->next = NULL;
		current_used->next->size = size - sizeof(t_header);
	}
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
