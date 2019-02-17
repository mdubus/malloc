/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_block_in_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:04:22 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/17 17:35:28 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	put_block_in_list(t_header **arena, t_header **next_block)
{
	t_header	*tmp;

	tmp = *arena;
	while (tmp != NULL && tmp->next != NULL && *next_block > tmp->next)
		tmp = tmp->next;
	if (tmp == *arena && *next_block < tmp->next)
	{
		(*next_block)->next = tmp;
		*arena = *next_block;
	}
	else
	{
		(*next_block)->next = tmp->next;
		tmp->next = *next_block;
	}
}

