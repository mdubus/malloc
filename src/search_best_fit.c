/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_best_fit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:16:34 by mdubus            #+#    #+#             */
/*   Updated: 2019/01/31 16:26:47 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_header	*search_best_fit(t_header *list, size_t size)
{
	t_header	*best_ptr;
	size_t		aligned_size;

	best_ptr = NULL;
	aligned_size = get_aligned_size(size);
	while (list != NULL)
	{
		if ((best_ptr == NULL || list->size < best_ptr->size) &&
				list->size >= aligned_size)
			best_ptr = list;
		list = list->next;
	}
	return (best_ptr);
}
