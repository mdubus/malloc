#include "../includes/malloc.h"

void	print_range(t_header *tmp)
{
	print_address((uintptr_t)tmp + sizeof(t_header));
	ft_putstr(" - ");
	print_address((uintptr_t)tmp + sizeof(t_header) + tmp->size);
	ft_putstr(" : ");
	ft_putnbr(tmp->size);
	ft_putstr(" octets\n");
}

void	show_alloc_mem()
{
	t_header	*tmp;
	int			arena_type;
	size_t		total_size;

	tmp = arena.used;
	arena_type = -1;
	total_size = 0;
	while(tmp != NULL)
	{
		if (arena_type == -1 || arena_type != get_arena_type(tmp->size))
		{
			print_arena_name(tmp->size);
			ft_putstr(" : ");
			print_address((uintptr_t)tmp);
			ft_putstr("\n");
		}
		arena_type = get_arena_type(tmp->size);
		print_range(tmp);
		total_size += tmp->size;
		tmp = tmp->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total_size);
	ft_putstr(" octets\n");
}
