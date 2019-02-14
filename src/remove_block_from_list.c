#include "../includes/malloc.h"

void	remove_block_from_list(t_header **list, t_header *block)
{
	t_header	*tmp;

	tmp = *list;
	if (*list == block)
		*list = block->next;
	else
	{
		while (tmp != NULL && tmp->next != NULL && tmp->next != block)
			tmp = tmp->next;
		tmp->next = block->next;
	}
}
