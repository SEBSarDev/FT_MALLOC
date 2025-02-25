/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:00:33 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 15:35:01 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block	*new_block(t_heap **heap, void *start, size_t size)
{
	t_block	*block;

	while ((*heap)->first_block && (*heap)->first_block->next)
		(*heap)->first_block = (*heap)->first_block->next;
	block = (t_block *)start;
	block->prev = (*heap)->first_block;
	block->start = start;
	block->start_data = start + sizeof(t_block);
	block->is_free = 0;
	block->total_size = size + sizeof(t_block);
	block->data_size = size;
	if ((*heap)->first_block)
		(*heap)->first_block->next = block;
	else
		(*heap)->first_block = block;
	replace_first_block(heap);
	(*heap)->used_size += block->total_size;
	(*heap)->free_size = (*heap)->heap_size - (*heap)->used_size;
	(*heap)->block_used++;
	return (block);
}

t_heap	*new_heap(void *start, size_t alloc_size)
{
	t_heap	*heap;

	heap = (t_heap *) start;
	heap->heap_size = alloc_size;
	heap->used_size = sizeof(t_heap);
	heap->free_size = heap->heap_size - heap->used_size;
	heap->block_used = 0;
	heap->start = start;
	heap->start_data = start + sizeof(t_heap);
	heap->first_block = NULL;
	heap->prev = NULL;
	heap->next = NULL;
	return (heap);
}

t_block	*allocate_new_heap(size_t size)
{
	size_t	alloc_size;
	void	*ptr;
	t_heap	*temp;
	t_block	*block;

	alloc_size = get_alloc_size(size);
	ptr = mmap(NULL, alloc_size,
			PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	temp = new_heap(ptr, alloc_size);
	block = new_block(&temp, ptr + sizeof(t_heap), size);
	temp->first_block = block;
	if (!g_heap)
		g_heap = temp;
	else
	{
		while (g_heap->next != NULL)
			g_heap = g_heap->next;
		temp->prev = g_heap;
		g_heap->next = temp;
		replace_g_heap();
	}
	return (block);
}
