#include "../includes/malloc.h"

t_arena	arena;

void	init_new_block(t_header *arena, size_t size)
{
	arena->next = NULL;
	arena->prev = NULL;
	arena->size = size;
}

void	*get_new_arena(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	init_new_block(ptr, size);
	return ptr;
}

t_header	*search_for_space(t_header *list, size_t size)
{
	t_header	*best_ptr;

	best_ptr = NULL;
	while (list != NULL)
	{
		if ((best_ptr == NULL || list->size < best_ptr->size) && list->size >= size)
			best_ptr = list;
		list = list->next;
	}
	printf("Best ptr size : %zu\n", best_ptr->size);
	return best_ptr;
}

void	*ft_malloc(size_t size)
{
	size_t		max_tiny;
	size_t		max_small;

	max_tiny = (size_t)MAX_TINY * getpagesize();
	max_small = (size_t)MAX_SMALL * getpagesize();
	/*	if ((void*)arena.tiny.free == NULL)
		arena.tiny.free = get_new_arena(max_tiny);
		if ((void*)arena.small.free == NULL)
		arena.small.free = get_new_arena(max_small);
		*/	
	if (size + sizeof(t_header) <= max_tiny)
	{
		return search_for_space(arena.tiny.free, size + sizeof(t_header));
		//	return (arena.tiny.free + sizeof(t_block));
	}
	else if (size + sizeof(t_header) <= max_small)
	{
		return search_for_space(arena.small.free, size + sizeof(t_header));
		//	return (arena.small.free + sizeof(t_block));
	}
	return NULL;
}
