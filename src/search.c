/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:00:45 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 16:35:23 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block	*choose_block(t_heap **heap, t_block **block, size_t size)
{
	t_block	*ret;

	ret = NULL;
	if ((*block)->data_size == size && (*block)->is_free)
	{
		(*block)->is_free = 0;
		(*heap)->block_used++;
		return (*block);
	}
	if ((*block)->data_size >= size + sizeof(t_block)
		&& (*block)->is_free)
		ret = divide_block(heap, block, size);
	return (ret);
}

t_block	*is_there_block(t_heap **heap, size_t size)
{
	t_block	*block;
	int		block_end;

	block = NULL;
	block_end = 0;
	while ((*heap)->first_block && !block_end)
	{
		block = choose_block(heap, &(*heap)->first_block, size);
		block_end = is_last_block(&(*heap)->first_block);
		if (block || block_end)
			break ;
		(*heap)->first_block = (*heap)->first_block->next;
	}
	if (!block && (*heap)->free_size >= sizeof(t_block) + size)
		block = new_block(heap, (*heap)->start + (*heap)->used_size, size);
	replace_first_block(heap);
	return (block);
}

t_block	*find_in_heap(size_t size, size_t heap_size)
{
	t_block	*block;
	int		heap_end;

	block = NULL;
	heap_end = 0;
	while (g_heap && !heap_end)
	{
		if (g_heap->heap_size == heap_size)
			block = is_there_block(&g_heap, size);
		heap_end = is_last_heap(&g_heap);
		if (block || heap_end)
			break ;
		g_heap = g_heap->next;
	}
	return (block);
}

t_block	*get_ptr_in_heap(void *ptr)
{
	int	heap_end;
	int	block_end;

	heap_end = 0;
	while (g_heap && !heap_end)
	{
		block_end = 0;
		while (g_heap->first_block && !block_end)
		{
			if (g_heap->first_block->start_data == ptr)
				return (g_heap->first_block);
			block_end = is_last_block(&g_heap->first_block);
			if (!block_end)
				g_heap->first_block = g_heap->first_block->next;
		}
		heap_end = is_last_heap(&g_heap);
		if (!heap_end)
			g_heap = g_heap->next;
	}
	return (NULL);
}
