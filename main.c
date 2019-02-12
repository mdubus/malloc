#include "includes/malloc.h"
#include <stdlib.h>

int	main(void)
{
	char	*str = ft_malloc(2097118);
	(void)str;
//	str = ft_malloc(30);

	printf("\nmax tiny : %zu\n\n",(size_t)MAX_TINY * getpagesize());
	show_alloc_mem();

	return 0;
}
