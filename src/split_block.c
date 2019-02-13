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

void	check_for_defragmentation(t_header **rest)
{
	if ((*rest)->next == *rest + sizeof(t_header) + (*rest)->size + 1)
	{
		(*rest)->size += (*rest)->next->size + sizeof(t_header);
		(*rest)->next = (*rest)->next->next;
	}
}

void	put_rest_in_free_list(t_header *best_fit, size_t size,
		t_header **current_arena)
{
	t_header	*rest;
	t_header	*tmp;
	size_t		aligned_size;

	tmp = *current_arena;
	aligned_size = get_aligned_size(size);
	rest = (void*)best_fit + aligned_size;
	rest->size = best_fit->size - aligned_size;
	if ((*current_arena)->next == NULL)
	{
		*current_arena = rest;
		(*current_arena)->next = NULL;
	}
	else
	{
		put_block_in_list(&tmp, &rest);
		check_for_defragmentation(&rest);
	}
}

void	put_block_in_used_list(t_header *best_fit, size_t size)
{
	t_header	*tmp;
	size_t		aligned_size;

	aligned_size = get_aligned_size(size);
	tmp = (void*)arena.used;
	// S'il n'y a pas de reste dans le best_fit, alors best_fit garde sa taille
	if (best_fit->size > aligned_size)
		best_fit->size = aligned_size - sizeof(t_header);
	if (arena.used == NULL)
	{
		arena.used = best_fit;
		arena.used->next = NULL;
	}
	else
		put_block_in_list(&tmp, &best_fit);
}

void	remove_block_from_list(t_header **list, t_header *block)
{
	t_header	*tmp;

	tmp = *list;
	if (*list == block)
		*list = block->next;
	else
	{
		while (tmp != NULL && tmp->next != NULL && tmp->next != block)
			tmp = tmp->next;
		tmp->next = block->next;
	}
}

void	split_block(t_header **current_arena, t_header *best_fit, size_t size)
{
	// Si le reste du best fit > 0, alors on rajoute le reste dans la liste des dispo
	if (best_fit->size > get_aligned_size(size))
	{
		put_rest_in_free_list(best_fit, size, current_arena);
		put_block_in_used_list(best_fit, size);
	}
	else
	{
		put_block_in_used_list(best_fit, size);
		remove_block_from_list(current_arena, best_fit);
	}
}
