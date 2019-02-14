#include "../includes/malloc.h"

void	ft_free(void	*ptr)
{
	t_header	*tmp;
	t_header	*my_ptr;
	//	t_header	*prev;
	int			arena_type;

	tmp = (void*)arena.used;
	my_ptr = (t_header *)ptr - sizeof(t_header);
	arena_type = -1;

	while (tmp != NULL && tmp != my_ptr)
	{
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		arena_type = get_arena_type(((t_header*)ptr)->size);
		if (arena_type == TINY)
		{
			put_block_in_list(&arena.tiny, &my_ptr);
			remove_block_from_list(&arena.used, my_ptr);
		}
		else if (arena_type == SMALL)
		{
			tmp = arena.small;
		}
		else
			munmap(ptr, ((t_header*)ptr)->size + sizeof(t_header));
	}
}
