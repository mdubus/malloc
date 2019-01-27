#ifndef MALLOC_H
#define MALLOC_H

#define MMAP_PROT (PROT_READ | PROT_WRITE)
#define MMAP_FLAGS (MAP_ANON | MAP_PRIVATE)
#define MAX_TINY	1024
#define MAX_SMALL	0

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

typedef struct	s_arena t_arena;
typedef struct	s_block t_block;
typedef struct	s_header t_header;

struct s_header {
	size_t		size;
	t_header	*prev;
	t_header	*next;
};

struct s_block {
	t_header	*free;
	t_header	*inUse;
};

struct s_arena {
	t_block	tiny;
	t_block small;
};

t_arena arena;

t_header	*search_best_fit(t_header *list, size_t size);
void		print_list(t_header *list);

#endif
