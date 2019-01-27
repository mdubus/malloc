#include "includes/malloc.h"
#include <stdlib.h>

int	main(void)
{
	char	*str = ft_malloc(7);
	(void)str;
	char	*str2 = ft_malloc(30);
	(void)str2;
	printf("********** FREE LIST **********\n");
	print_list(arena.tiny.free);
	printf("********** IN USE LIST **********\n");
	print_list(arena.tiny.inUse);

	return 0;
}
