/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:01:37 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 16:28:49 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*enlarge_block(size_t size, size_t size_dif)
{
	if (g_heap->first_block->next->total_size == size_dif)
	{
		if (g_heap->first_block->next->next)
			g_heap->first_block->next->next->prev = g_heap->first_block;
		g_heap->first_block->next = g_heap->first_block->next->next;
	}
	else
		merge_end_to_free(&g_heap->first_block, size, size_dif);
	g_heap->first_block->data_size = size;
	g_heap->first_block->total_size = size + sizeof(t_block);
	ft_memset(g_heap->first_block->next - size_dif, 0, size_dif);
	return (g_heap->first_block->start_data);
}

void	*reduce_block(size_t size, size_t size_dif)
{
	ft_memset(g_heap->first_block->next + size, 0, size_dif);
	if (!g_heap->first_block->next)
	{
		g_heap->used_size -= size_dif;
		g_heap->free_size += size_dif;
	}
	if (g_heap->first_block->next && g_heap->first_block->next->is_free == 0
		&& size_dif >= sizeof(t_block))
	{
		divide_block(&g_heap, &g_heap->first_block, size);
		g_heap->block_used--;
	}
	if (g_heap->first_block->next && g_heap->first_block->next->is_free == 1)
		merge_end_to_free(&g_heap->first_block, size, size_dif * (-1));
	g_heap->first_block->data_size = size;
	g_heap->first_block->total_size = size + sizeof(t_block);
	return (g_heap->first_block->start_data);
}

void	*new_space(t_block *block, size_t size)
{
	size_t	size_dif;

	size_dif = size - block->data_size;
	if (size_dif == 0)
		return (g_heap->first_block->start_data);
	if (size_dif <= 0)
	{
		reduce_block(size, size_dif * (-1));
		return (g_heap->first_block->start_data);
	}
	if (block->next && block->next->is_free == 1
		&& (block->next->total_size == size_dif
			|| block->next->data_size >= size_dif))
		return (enlarge_block(size, size_dif));
	if (!block->next && g_heap->free_size >= size_dif)
	{
		ft_memset(g_heap->first_block->next + size, 0, size_dif);
		g_heap->first_block->data_size = size;
		g_heap->first_block->total_size = size + sizeof(t_block);
		g_heap->used_size += size_dif;
		g_heap->free_size -= size_dif;
		return (g_heap->first_block->start_data);
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex_malloc);
	if (ptr == NULL || !g_heap)
		return (NULL);
	block = get_ptr_in_heap(ptr);
	if (!block)
		return (NULL);
	new_ptr = new_space(block, size);
	replace_first_block(&g_heap);
	replace_g_heap();
	if (!new_ptr)
	{
		new_ptr = run_malloc(size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, block->data_size);
			run_free(ptr);
		}
		else
			new_ptr = ptr;
	}
	pthread_mutex_unlock(&g_mutex_malloc);
	return (new_ptr);
}
