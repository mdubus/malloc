#include "../includes/malloc.h"

size_t	get_aligned_size(size_t size)
{
	size_t	aligned_size;

	aligned_size = size;
	if (aligned_size % sizeof(long) != 0)
		aligned_size += (sizeof(long) - aligned_size % sizeof(long));
	return (aligned_size);
}
