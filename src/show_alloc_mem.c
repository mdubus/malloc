/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:34:46 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 14:22:52 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	print_header(t_header *list)
{
	void	*begin_address;
	void	*end_address;

	begin_address = list;
	end_address = (void*)list + sizeof(t_header);
	ft_print_address((uintptr_t)begin_address);
	ft_putstr("\x1B[35m - header - \x1B[0m");
	ft_print_address((uintptr_t)end_address);
}

void	print_size(t_header *list)
{
	void	*end_address;
	char	size[21];

	end_address = (void*)list + sizeof(t_header) + list->size;
	ft_putstr("\x1B[36m - size : ");
	ft_utoa_base_r(size, list->size, 10);
	ft_putstr(size);
	ft_putstr(" - \x1B[0m");
	ft_print_address((uintptr_t)end_address);
}

void	print_padding(t_header *list, size_t *total_padding)
{
	size_t	aligned_size;
	void	*end_address;
	char	size[21];

	aligned_size = list->size;
	if (aligned_size % sizeof(long) != 0)
		aligned_size = aligned_size + (sizeof(long) - aligned_size % sizeof(long));
	end_address = (void*)list + sizeof(t_header) + aligned_size;
	ft_putstr("\x1B[94m - padding : ");
	ft_utoa_base_r(size, (aligned_size - list->size), 10);
	ft_putstr(size);
	ft_putstr(" - \x1B[0m");
	ft_print_address((uintptr_t)end_address);
	ft_putstr("\n");
	*total_padding += (aligned_size - list->size);
}

void	show_alloc_mem(void)
{
	size_t	total_header;
	size_t	total_size;
	size_t	total_padding;

	total_header = 0;
	total_size = 0;
	total_padding = 0;
	ft_putstr("List in use : \n");
	while (arena.used != NULL)
	{
		print_header(arena.used);
		print_size(arena.used);
		print_padding(arena.used, &total_padding);
		total_size += arena.used->size;
		total_header += sizeof(t_header);
		arena.used = arena.used->next;
	}
	printf("\nTotal used : \x1B[35m header : %zu \x1B[0m | ", total_header);
	printf("\x1B[36m size : %zu \x1B[0m | ", total_size);
	printf("\x1B[94m padding : %zu \x1B[0m -> %zu\n\n", total_padding, total_padding + total_size + total_header);
	fflush(stdout);

	ft_putstr("\nTiny free list : \n");
	while (arena.tiny != NULL)
	{
		print_header(arena.tiny);
		print_size(arena.tiny);
		print_padding(arena.tiny, &total_padding);
		total_size += arena.tiny->size;
		total_header += sizeof(t_header);
		arena.tiny = arena.tiny->next;
	}
	printf("\nTotal reserved : %zu\n", total_header + total_size + total_padding);
}
