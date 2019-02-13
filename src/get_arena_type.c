#include "../includes/malloc.h"

int		get_arena_type(size_t size)
{
	size_t		max_tiny;
	size_t		max_small;

	max_tiny = (size_t)MAX_TINY * getpagesize();
	max_small = (size_t)MAX_SMALL * getpagesize();
	if (size <= max_tiny)
		return(TINY);
	else if (size <= max_small)
		return(SMALL);
	else
		return(LARGE);
}
