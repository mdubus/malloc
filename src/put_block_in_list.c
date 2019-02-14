/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_block_in_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:04:22 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 16:04:46 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	put_block_in_list(t_header **tmp, t_header **next_block)
{
	t_header	*prev;
	if (*tmp == NULL)
	{
		*tmp = *next_block;
		(*tmp)->next = NULL;
	}
	while (*tmp && (*tmp)->next != NULL && *next_block > (*tmp)->next)
	{
		prev = *tmp;
		*tmp = (*tmp)->next;
	}
	if ((*tmp)->next == NULL)
	{
		if (*next_block > *tmp)
		{
			(*tmp)->next = *next_block;
			(*tmp)->next->next = NULL;
		}
		else
		{
			(*next_block)->next = *tmp;
			*tmp = *next_block;
			prev = *tmp;
		}
		check_for_defragmentation(&prev);
	}
	else
	{
		(*next_block)->next = (*tmp)->next;
		(*tmp)->next = *next_block;
	}
}
