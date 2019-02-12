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
		*current_arena = get_new_arena(max_arena_size + sizeof(t_header));
	if (*current_arena == NULL)
		return (NULL);
	best_fit = search_best_fit(*current_arena, size);
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
	t_header	*large;
	t_header	*tmp;

	if (size + sizeof(t_header) <= sizeof(t_header))
		return NULL;
	max_tiny = (size_t)(MAX_TINY * getpagesize());
	max_small = (size_t)(MAX_SMALL * getpagesize());
	large = NULL;
	if (size <= max_tiny)
		return (get_mallocked_zone(&arena.tiny, max_tiny, size));
	if (size <= max_small)
		return (get_mallocked_zone(&arena.small, max_small, size));
	else
	{
		tmp = arena.used;
		large = get_new_arena(get_aligned_size(size + sizeof(t_header)));
		if (large == NULL)
			return (NULL);
		put_block_in_list(&tmp, &large);
		return (large + sizeof(t_header));
	}
}
