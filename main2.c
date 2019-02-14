/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_06_malloc_a_lot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:21:03 by mressier          #+#    #+#             */
/*   Updated: 2017/04/06 14:21:04 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

#define	STRING_SIZE		20

#define	NB_TEST 200

int		main(void)
{
	unsigned int	i;
	void			*ret[NB_TEST];

	for (i = 0; i < NB_TEST; i++)
	{
		ret[i] = ft_malloc(STRING_SIZE);
		memset(ret[i], 'a', STRING_SIZE);
	show_alloc_mem();
	}

//	for (i = 0; i < NB_TEST; i++)
//	{
//		ret[i] = realloc(ret[i], STRING_SIZE * 5);
//		memset(ret[i] + STRING_SIZE, 'b', STRING_SIZE * 4);
//	}

	for (i = 0; i < NB_TEST; i++)
	{
		ft_free(ret[i]);
		ret[i] = NULL;
	}
	show_alloc_mem();

	return (0);
}
