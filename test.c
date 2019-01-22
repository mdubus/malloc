#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int	main(void)
{
	char	*text;
	int		errno;

	errno = -1;
	text = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	strcpy(text, "coucou\n");
	printf("%p\n", text);
	if ((munmap(text, getpagesize())) == -1) {
		printf("Error : %s\n", strerror(errno));
	}
	else {
		printf("%s\n", "munmap succeeded");
	}
	return 0;
}
