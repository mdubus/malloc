#ifndef MALLOC_H
#define MALLOC_H

#define MMAP_PROT (PROT_READ | PROT_WRITE)
#define MMAP_FLAGS (MAP_ANON | MAP_PRIVATE)

// On mac, 2^21 is the max size for tiny arenas.
// 2^21 / 4096 (pagesize) = 512
#define MAX_TINY	512

// On max, 2^24 is the max size for small arenas.
// 2^24 / 4096 (pagesize) = 4096
#define MAX_SMALL	4096

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>



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

/* ft_print_address */
char	*ft_strrev(char	*str);
char	*ft_utoa_base_r(char *buf, unsigned long long n, unsigned base);
void	ft_print_address(uintptr_t ptr);

/* malloc */

void	init_new_block(t_header *arena, size_t size);
void	*get_new_arena(size_t size);
void	split_block(t_block *arena, t_header *best_fit, size_t size);
void	*ft_malloc(size_t size);

/* search_best_fit */

t_header	*search_best_fit(t_header *list, size_t size);

/* show_alloc_mem */

size_t	ft_strlen(const char *s);
void	ft_putstr(char *str);
void	print_list(t_header *list);
void	show_alloc_mem();

#endif
