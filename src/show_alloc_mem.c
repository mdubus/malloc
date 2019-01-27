/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:34:46 by mdubus            #+#    #+#             */
/*   Updated: 2019/01/27 16:55:39 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	print_list(t_header *list)
{
	char	size[21];

	ft_print_address((uintptr_t)list);
	write(1, "\n\n", 2);
	while (list != NULL)
	{
		ft_print_address((uintptr_t)list);
		ft_putstr("\x1B[35m - header - \x1B[0m");
		ft_print_address((uintptr_t)list + sizeof(t_header));
		ft_putstr("\x1B[36m - size : ");
		ft_utoa_base_r(size, list->size, 10);
		ft_putstr(size);
		ft_putstr(" - \x1B[0m");
		ft_print_address((uintptr_t)list + sizeof(t_header) + list->size);
		ft_putstr("\x1B[94m - padding : ");
		ft_putstr(" - \x1B[0m");
		write(1, "\n", 1);
		list = list->next;
	}
	write(1, "\n", 1);
}

void	show_alloc_mem(void)
{
	if (arena.tiny.inUse != NULL)
	{
		ft_putstr("\nTINY : ");
		print_list(arena.tiny.inUse);
	}
	if (arena.small.inUse != NULL)
	{
		ft_putstr("\nSMALL : ");
		print_list(arena.small.inUse);
	}
}
