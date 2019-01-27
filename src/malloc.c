/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:53:57 by mdubus            #+#    #+#             */
/*   Updated: 2019/01/27 17:43:21 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	init_new_block(t_header *arena, size_t size)
{
	arena->next = NULL;
	arena->prev = NULL;
	arena->size = size;
}

void	*get_new_arena(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	init_new_block(ptr, size);
	return ptr;
}

void	split_block(t_block *arena, t_header *best_fit, size_t size)
{
	// padding

	// ON LINK LE NOUVEAU MORCEAU DISPO DANS FREE
	// A-t-on la place dans le morceau restant pour stocker un header ?
	// Si oui, on cree un nouveau maillon (ci-dessous)
	// Si non, on defragmente si on peut.
	// Si pas de defrag, on le laisse avec le maillon inUse
	if (best_fit->prev != NULL)
	{
		best_fit->prev->next = best_fit + size;
		(best_fit + size)->prev = best_fit->prev;
	}
	else
	{
		arena->free = (void*)best_fit + size;
		arena->free->prev = NULL;
	}
	if (best_fit->next != NULL)
	{
		(best_fit + size)->next = best_fit->next;
		best_fit->next->prev = (best_fit + size);
	}
	else
	{
		(best_fit + size)->next = NULL;
	}
	printf("free available space : %zu\n", best_fit->size - size - sizeof(t_header));
	printf("%p\n", (void*)best_fit + size);
	(best_fit + size)->size = best_fit->size - size - sizeof(t_header);


	// ON LINK LE NOUVEAU MAILLON PRIS DANS IN USE
	// On le met tout a la fin pour le moment. Penser a les trier par adresse
	while (arena->inUse && arena->inUse->next != NULL)
		arena->inUse = arena->inUse->next;
	if (arena->inUse != NULL)
	{
		arena->inUse->next = best_fit;
		arena->inUse->next->prev = arena->inUse;
		arena->inUse->next->next = NULL;
		arena->inUse->next->size = size - sizeof(t_header);
	}
	else
	{
		arena->inUse = best_fit;
		arena->inUse->size = size - sizeof(t_header);
		arena->inUse->next = NULL;
		arena->inUse->prev = NULL;
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


	if ((void*)arena.tiny.free == NULL)
		arena.tiny.free = get_new_arena(max_tiny);
	if ((void*)arena.small.free == NULL)
		arena.small.free = get_new_arena(max_small);
	if (arena.tiny.free == NULL || arena.small.free == NULL)
		return NULL;

	if (size + sizeof(t_header) <= max_tiny)
	{
		best_fit = search_best_fit(arena.tiny.free, size + sizeof(t_header));
		if (best_fit == NULL)
		{
			// Get new arena and pu it in the free list, ordered by addresses
			best_fit = get_new_arena(max_tiny);
			return best_fit;
		}
		else
		{
			split_block(&arena.tiny, best_fit, size + sizeof(t_header));
			printf("%zu\n\n", arena.tiny.free->size);
			return best_fit + sizeof(t_header);
		}//	return (arena.tiny.free + sizeof(t_block));
	}
	else if (size + sizeof(t_header) <= max_small)
	{
		best_fit = search_best_fit(arena.small.free, size + sizeof(t_header));
		if (best_fit == NULL)
		{
			best_fit = get_new_arena(max_small);
			return best_fit;
		}
		else
		{
			split_block(&arena.small, best_fit, size + sizeof(t_header));
			return best_fit + sizeof(t_header);
		}
		//	return (arena.small.free + sizeof(t_block));
	}
	return NULL;
}
