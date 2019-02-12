#include "../includes/malloc.h"

t_header	*get_current_arena(size_t size)
{
	size_t		max_tiny;
	size_t		max_small;

	max_tiny = (size_t)MAX_TINY * getpagesize();
	max_small = (size_t)MAX_SMALL * getpagesize();
	if (size + sizeof(t_header) <= max_tiny)
		return (arena.tiny);
	else if (size + sizeof(t_header) <= max_small)
		return (arena.small);
	return (arena.large);
}
