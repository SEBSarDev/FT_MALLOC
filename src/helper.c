/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:00:55 by ssar              #+#    #+#             */
/*   Updated: 2024/05/15 12:32:01 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/*each tiny heap will have around 127 block of size (16 * getpagesize)/128*/
/*each small heap will have around 128 block of size (32 * getpagesize)/128*/
size_t	get_alloc_size(size_t size)
{
	size_t	alloc_size;
	size_t	tiny;
	size_t	small;
	int		page_size;

	page_size = getpagesize();
	tiny = (size_t)(16 * page_size);
	small = (size_t)(32 * page_size);
	alloc_size = size;
	if (size > small / 128)
		alloc_size += sizeof(t_block);
	if (size <= small / 128)
		alloc_size = small;
	if (size <= tiny / 128)
		alloc_size = tiny;
	alloc_size += sizeof(t_heap);
	return (alloc_size);
}

int	is_last_heap(t_heap **heap)
{
	if ((*heap)->next == NULL)
	{
		while ((*heap)->prev)
			*heap = (*heap)->prev;
		return (1);
	}
	return (0);
}

int	is_last_block(t_block **block)
{
	if ((*block)->next == NULL)
	{
		while ((*block)->prev)
			*block = (*block)->prev;
		return (1);
	}
	return (0);
}

void	replace_first_block(t_heap **heap)
{
	while ((*heap)->first_block && (*heap)->first_block->prev)
		(*heap)->first_block = (*heap)->first_block->prev;
}

void	replace_g_heap(void)
{
	if (g_heap)
	{
		while (g_heap->prev)
			g_heap = g_heap->prev;
	}
}
