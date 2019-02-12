/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:34:46 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 16:32:43 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	print_arena_name(size_t size)
{
	size_t		max_tiny;
	size_t		max_small;

	max_tiny = (size_t)MAX_TINY * getpagesize();
	max_small = (size_t)MAX_SMALL * getpagesize();
	if (size <= max_tiny)
		ft_putstr("TINY  - ");
	else if (size <= max_small)
		ft_putstr("SMALL - ");
	else
		ft_putstr("LARGE - ");
}

void	print_header(t_header *list)
{
	void	*begin_address;
	void	*end_address;

	begin_address = list;
	end_address = (void*)list + sizeof(t_header);
	print_address((uintptr_t)begin_address);
	ft_putstr("\x1B[35m - header - \x1B[0m");
	print_address((uintptr_t)end_address);
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
	print_address((uintptr_t)end_address);
	write(1, "\n", 1);
}

void	print_free_list(t_header *list)
{
	size_t	total_header;
	size_t	total_size;

	total_header = 0;
	total_size = 0;
	while (list != NULL)
	{
		print_header(list);
		print_size(list);
		total_size += list->size;
		total_header += sizeof(t_header);
		list = list->next;
	}
	printf("\nTotal reserved : %zu\n", total_header + total_size);
}

void	show_alloc_mem(void)
{
	size_t	total_header;
	size_t	total_size;

	total_header = 0;
	total_size = 0;
	ft_putstr("List in use : \n");
	while (arena.used != NULL)
	{
		print_arena_name(arena.used->size);
		print_header(arena.used);
		print_size(arena.used);
		total_size += arena.used->size;
		total_header += sizeof(t_header);
		arena.used = arena.used->next;
	}
	printf("\nIn use : \x1B[35m header : %zu \x1B[0m | ", total_header);
	printf("\x1B[36m size : %zu \x1B[0m | ", total_size);
	printf("total : %zu", total_size + total_header);
	fflush(stdout);
	ft_putstr("\n\n--------------------------\n");
	ft_putstr("Tiny free list : \n");
	print_free_list(arena.tiny);
	ft_putstr("\n--------------------------\n");
	ft_putstr("Small free list : \n");
	print_free_list(arena.small);
}
