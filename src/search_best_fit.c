/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_best_fit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:16:34 by mdubus            #+#    #+#             */
/*   Updated: 2019/01/27 10:17:11 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_header	*search_best_fit(t_header *list, size_t size)
{
	t_header	*best_ptr;

	best_ptr = NULL;
	while (list != NULL)
	{
		if ((best_ptr == NULL || list->size < best_ptr->size) && list->size >= size)
			best_ptr = list;
		list = list->next;
	}
	return best_ptr;
}
