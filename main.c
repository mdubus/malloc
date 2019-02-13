#include "includes/malloc.h"
#include <stdlib.h>

int	main(void)
{
char	*str = ft_malloc(20);
//	char	*str = ft_malloc(2097152);
	str = ft_malloc(1);
//	(void)str;
//	str = ft_malloc(16777100);
//	str = ft_malloc(30000001);
	str = ft_malloc(0);
	str = ft_malloc(-1);


	printf("\nmax tiny : %zu",(size_t)MAX_TINY * getpagesize());
	printf("\nmax small : %zu\n\n",(size_t)MAX_SMALL * getpagesize());
	show_alloc_mem();
	printf("\n **************************** \n");
	my_show_alloc_mem();

	return 0;
}
