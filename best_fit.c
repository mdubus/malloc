#include "includes/malloc.h"

t_arena arena;

t_header	*new_header(size_t size)
{
	t_header	*mew;

	mew = NULL;
	mew = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	mew->prev = NULL;
	mew->next = NULL;
	mew->size = size;
	return mew;
}

int	main(void)
{
	t_header	*begin;
	t_header	*current;

	begin = NULL;
	current = NULL;

	arena.tiny.free = new_header(2);
	begin = arena.tiny.free;
	current = arena.tiny.free;
	current->size = 2;
	current->next = new_header(31);
	current = current->next;
	current->next = new_header(40);

	current = search_best_fit(begin, 2);
	printf("Best fit: %zu\n", current->size);
	current = search_best_fit(begin, 7);
	printf("Best fit: %zu\n", current->size);
	current = search_best_fit(begin, 31);
	printf("Best fit: %zu\n", current->size);
	current = search_best_fit(begin, 32);
	printf("Best fit: %zu\n", current->size);
	current = search_best_fit(begin, 41);
	if (current == NULL)
		printf("Best fit : NULL\n");
	else
		printf("Best fit: %zu\n", current->size);

	return 0;
}
