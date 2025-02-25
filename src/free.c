/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:00:46 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 16:15:44 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

int	is_there_another(t_heap *heap, size_t heap_size)
{
	int		page_size;
	size_t	tiny;
	size_t	small;
	void	*stock_addr;

	page_size = getpagesize();
	tiny = (size_t)(16 * page_size + sizeof(t_heap));
	small = (size_t)(32 * page_size + sizeof(t_heap));
	if (heap_size != tiny && heap_size != small)
		return (1);
	stock_addr = heap->start;
	while (heap->prev)
		heap = heap->prev;
	while (heap)
	{
		if (heap->heap_size == heap_size
			&& heap->start != stock_addr)
			return (1);
		if (heap->next == NULL)
			break ;
		heap = heap->next;
	}
	return (0);
}

void	free_heap(t_heap **heap)
{
	size_t	size;
	t_heap	*first_heap;
	int		res;

	res = is_there_another(*heap, (*heap)->heap_size);
	first_heap = *heap;
	size = (*heap)->heap_size;
	if (res)
	{
		if ((*heap)->prev)
			(*heap)->prev->next = (*heap)->next;
		if ((*heap)->next)
			(*heap)->next->prev = (*heap)->prev;
		if ((*heap)->prev == NULL)
			first_heap = (*heap)->next;
		if ((*heap)->next == NULL)
			first_heap = (*heap)->prev;
		munmap((*heap)->start, size);
		g_heap = first_heap;
	}
}

void	free_block(t_heap **heap, t_block **block)
{
	ft_memset((*block)->start_data, 0, (*block)->data_size);
	(*block)->is_free = 1;
	(*heap)->block_used--;
	if ((*block)->next && (*block)->next->is_free == 1)
		merge_blocks(block);
	if ((*block)->prev && (*block)->prev->is_free == 1)
	{
		*block = (*block)->prev;
		merge_blocks(block);
	}
	if ((*block)->next == NULL)
		merge_end(heap, block);
	replace_first_block(heap);
	if ((*heap)->block_used == 0)
		free_heap(heap);
	replace_g_heap();
}

void	run_free(void *ptr)
{
	int	heap_end;
	int	block_end;

	if (ptr == NULL || !g_heap)
		return ;
	heap_end = 0;
	while (g_heap && !heap_end)
	{
		block_end = 0;
		while (g_heap->first_block && !block_end)
		{
			if (g_heap->first_block->start_data == ptr)
			{
				free_block(&g_heap, &g_heap->first_block);
				return ;
			}
			block_end = is_last_block(&g_heap->first_block);
			if (!block_end)
				g_heap->first_block = g_heap->first_block->next;
		}
		heap_end = is_last_heap(&g_heap);
		if (!heap_end)
			g_heap = g_heap->next;
	}
	return ;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex_malloc);
	run_free(ptr);
	pthread_mutex_unlock(&g_mutex_malloc);
	return ;
}
