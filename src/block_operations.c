/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:00:20 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 16:21:08 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block	*divide_block(t_heap **heap, t_block **block, size_t size)
{
	t_block	*next_block;
	size_t	new_size;
	size_t	data_size_before;
	void	*start;

	data_size_before = (*block)->data_size;
	start = (*block)->start_data + size;
	(*block)->is_free = 0;
	(*block)->data_size = size;
	(*block)->total_size = size + sizeof(t_block);
	next_block = (t_block *)start;
	next_block->prev = *block;
	next_block->start = start;
	next_block->start_data = start + sizeof(t_block);
	next_block->is_free = 1;
	new_size = data_size_before - (size + sizeof(t_block));
	next_block->total_size = new_size + sizeof(t_block);
	next_block->data_size = new_size;
	next_block->next = (*block)->next;
	(*block)->next = next_block;
	(*heap)->block_used++;
	return (*block);
}

void	merge_end_to_free(t_block **block, size_t size, size_t size_dif)
{
	t_block	**stock_next;
	size_t	stock_size;
	void	*start;

	stock_next = &(*block)->next->next;
	stock_size = (*block)->next->data_size;
	start = (*block)->start_data + size;
	(*block)->next = (t_block *)start;
	(*block)->next->prev = (*block);
	(*block)->next->start = start;
	(*block)->next->start_data = start + sizeof(t_block);
	(*block)->next->is_free = 1;
	(*block)->next->data_size = stock_size - size_dif;
	(*block)->next->total_size = (*block)->next->data_size + sizeof(t_block);
	(*block)->next->next = *stock_next;
}

void	merge_blocks(t_block **block)
{
	(*block)->data_size += (*block)->next->total_size;
	(*block)->total_size = (*block)->data_size + sizeof(t_block);
	(*block)->next->prev = *block;
	(*block)->next = (*block)->next->next;
}

void	merge_end(t_heap **heap, t_block **block)
{
	(*heap)->free_size += (*block)->total_size;
	(*heap)->used_size -= (*block)->total_size;
	if ((*block)->prev)
		(*block)->prev->next = NULL;
	else
	{
		*block = NULL;
		(*heap)->first_block = NULL;
	}
}
