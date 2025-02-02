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

#define TINY	0
#define SMALL	1
#define LARGE	2

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
	t_header	*next;
};

struct s_arena {
	t_header	*tiny;
	t_header	*small;
	t_header	*used;
};

t_arena arena;

/* print_address */
char	*ft_strrev(char	*str);
char	*ft_utoa_base_r(char *buf, unsigned long long n, unsigned base);
void	print_address(uintptr_t ptr);

/* get arena name */
void	print_arena_name(size_t size);

/* get arena type */
int		get_arena_type(size_t size);

/* get new arena */
void	init_new_block(t_header *arena, size_t size);
void	*get_new_arena(size_t size);

/* malloc */

void	split_block(t_header **arena, t_header *best_fit, size_t size);
void	*ft_malloc(size_t size);

/* search_best_fit */

t_header	*search_best_fit(t_header *list, size_t size);

/* remove block from list */
void	remove_block_from_list(t_header **list, t_header *block);

/* free */
void	ft_free(void	*ptr);

/* ft_utils */
size_t	ft_strlen(const char *s);
void	ft_putstr(char *str);
void	ft_putnbr(size_t size);

/*get aligned size */
size_t	get_aligned_size(size_t size);

/* my_show_alloc_mem */

void	my_show_alloc_mem();
void	print_size(t_header *list);
void	print_header(t_header *list);

/* put block in list */
void	put_block_in_list(t_header **tmp, t_header **next_block);

/* split block */
void	split_block(t_header **current_arena, t_header *best_fit, size_t size);
void	put_block_in_used_list(t_header *best_fit, size_t size);
void	put_rest_in_free_list(t_header *best_fit, size_t size,
		t_header **current_arena);
void	check_for_defragmentation(t_header **ptr);

/* show alloc mem */
void	show_alloc_mem();

#endif
