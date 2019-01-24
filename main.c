#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
//	printf("%p\n", malloc(1));
	char *ptr = malloc(7);
	strcpy(ptr, "coucou\0");
	printf("%s\n", ptr);
	return 0;
}
