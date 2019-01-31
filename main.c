#include "includes/malloc.h"
#include <stdlib.h>

int	main(void)
{
	char	*str = ft_malloc(10);
//	(void)str;
	str = ft_malloc(20);
	str = ft_malloc(26);

//	char	*str2 = ft_malloc(30);
//	(void)str2;
	printf("\nmax tiny : %zu\n\n",(size_t)MAX_TINY * getpagesize());
	show_alloc_mem();

	return 0;
}
