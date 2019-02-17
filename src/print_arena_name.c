#include "../includes/malloc.h"

void	print_arena_name(size_t size)
{
	int	type;

	type = get_arena_type(size);
	if (type == TINY)
		ft_putstr("TINY  ");
	else if (type == SMALL)
		ft_putstr("SMALL ");
	else
		ft_putstr("LARGE ");
}
