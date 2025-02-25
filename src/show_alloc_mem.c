/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:48:45 by ssar              #+#    #+#             */
/*   Updated: 2024/05/15 12:35:31 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	print_infos_heap(t_heap **heap)
{
	int		page_size;
	size_t	tiny;
	size_t	small;

	page_size = getpagesize();
	tiny = (size_t)(16 * page_size + sizeof(t_heap));
	small = (size_t)(32 * page_size + sizeof(t_heap));
	if ((*heap)->heap_size == tiny)
		print_addr("TINY : ", (*heap)->start);
	else if ((*heap)->heap_size == small)
		print_addr("SMALL : ", (*heap)->start);
	else
		print_addr("LARGE : ", (*heap)->start);
	print_s("\n");
}

void	print_infos_block(t_block **block)
{
	print_addr("", (*block)->start_data);
	print_s(" - ");
	print_addr("", (*block)->start_data + (*block)->data_size);
	print_bytes(" : ", (*block)->data_size);
}

void	show_alloc_mem(void)
{
	int		heap_end;
	int		block_end;
	size_t	total;

	heap_end = 0;
	total = 0;
	while (g_heap && !heap_end)
	{
		block_end = 0;
		total += g_heap->heap_size;
		print_infos_heap(&g_heap);
		while (g_heap->first_block && !block_end)
		{
			print_infos_block(&g_heap->first_block);
			block_end = is_last_block(&g_heap->first_block);
			if (!block_end)
				g_heap->first_block = g_heap->first_block->next;
		}
		heap_end = is_last_heap(&g_heap);
		if (!heap_end)
			g_heap = g_heap->next;
	}
	print_bytes("Total : ", total);
	return ;
}
