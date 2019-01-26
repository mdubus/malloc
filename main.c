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
	t_header	*one;

	one = NULL;

	arena.tiny.free = mmap(0, 2, MMAP_PROT, MMAP_FLAGS, -1, 0);
	one = arena.tiny.free;
	one->size = 2;
	one->next = new_header(31);
	one = one->next;
	one->next = new_header(40);

	char *ptr = ft_malloc(7);
	if (ptr != NULL) {
		strcpy(ptr, "coucou");
		printf("%s\n", ptr);
	}
	else {
		printf("Couldn't allocate memory\n");
	}
	return 0;
}
