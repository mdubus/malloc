#include "includes/malloc.h"
#include <stdlib.h>

int	main(void)
{
char	*str = ft_malloc(7);
(void)str;
//	char	*str = ft_malloc(2097152);
char	*str2 = ft_malloc(1);
(void) str2;
//	(void)str;
	str = ft_malloc(16777100);
	str = ft_malloc(30000001);
	str = ft_malloc(0);
	str = ft_malloc(-1);


//	printf("\nmax tiny : %zu\n",(size_t)MAX_TINY * getpagesize());
//	printf("\nmax small : %zu\n\n",(size_t)MAX_SMALL * getpagesize());
//	show_alloc_mem();
//	printf("\n **************************** \n");
	my_show_alloc_mem();
//	ft_free(str);
//	printf("\n\n\n");
//	my_show_alloc_mem();

	return 0;
}
