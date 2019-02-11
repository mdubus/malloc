/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:53:57 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 16:27:16 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_mallocked_zone(t_header **current_arena, size_t max_arena_size, size_t size)
{
	t_header	*best_fit;
	t_header	*tmp;
	best_fit = NULL;
	tmp = NULL;
	if (*current_arena == NULL)
		*current_arena = get_new_arena(max_arena_size);
	if (*current_arena == NULL)
		return (NULL);
	best_fit = search_best_fit(*current_arena, size + sizeof(t_header));
	if (best_fit == NULL)
	{
		tmp = *current_arena;
		best_fit = get_new_arena(max_arena_size);
		put_block_in_list(&tmp, &best_fit);
		return best_fit;
	}
	else
	{
		split_block(current_arena, best_fit, size + sizeof(t_header));
		return best_fit + sizeof(t_header);
	}
	return (best_fit);
}

void	*ft_malloc(size_t size)
{
	size_t		max_tiny;
	size_t		max_small;

	if (size <= 0)
		return NULL;
	max_tiny = (size_t)MAX_TINY * getpagesize();
	max_small = (size_t)MAX_SMALL * getpagesize();

	if (size + sizeof(t_header) <= max_tiny)
		return get_mallocked_zone(&arena.tiny, max_tiny, size);
	if (size + sizeof(t_header) <= max_small)
		return get_mallocked_zone(&arena.small, max_small, size);
	return (NULL);
}
