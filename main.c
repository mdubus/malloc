#include "includes/malloc.h"
#include <stdlib.h>

int	main(void)
{
	char	*str = ft_malloc(1);
	(void)str;

	char	*str2 = ft_malloc(30);
	(void)str2;
	show_alloc_mem();

	return 0;
}
