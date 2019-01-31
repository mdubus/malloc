#ifndef MALLOC_H
#define MALLOC_H

#define MMAP_PROT (PROT_READ | PROT_WRITE)
#define MMAP_FLAGS (MAP_ANON | MAP_PRIVATE)
#define PADDING		16

// On mac, 2^21 is the max size for tiny arenas.
// 2^21 / 4096 (pagesize) = 512
#define MAX_TINY	512

// On max, 2^24 is the max size for small arenas.
// 2^24 / 4096 (pagesize) = 4096
#define MAX_SMALL	4096

#define padding		16

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

struct s_arena {
	t_header	*tiny;
	t_header	*small;
	t_header	*large;
	t_header	*used;
};

t_arena arena;

/* ft_print_address */
char	*ft_strrev(char	*str);
char	*ft_utoa_base_r(char *buf, unsigned long long n, unsigned base);
void	ft_print_address(uintptr_t ptr);

/* get new arena */
void	init_new_block(t_header *arena, size_t size);
void	*get_new_arena(size_t size);

/* malloc */

void	split_block(t_header **arena, t_header *best_fit, size_t size);
void	*ft_malloc(size_t size);

/* search_best_fit */

t_header	*search_best_fit(t_header *list, size_t size);

/* ft_putstr */
size_t	ft_strlen(const char *s);
void	ft_putstr(char *str);

/* show_alloc_mem */

void	show_alloc_mem();
void	print_padding(t_header	*list, size_t *total_padding);
void	print_size(t_header *list);
void	print_header(t_header *list);

#endif
