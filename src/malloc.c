/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:01:22 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 16:35:40 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

pthread_mutex_t	g_mutex_malloc;
t_heap			*g_heap;

t_block	*find_available_block(size_t size)
{
	t_block	*block;
	size_t	tiny;
	size_t	small;
	int		page_size;

	page_size = getpagesize();
	tiny = (size_t)(16 * page_size);
	small = (size_t)(32 * page_size);
	if (!g_heap || size > small / 128)
		return (NULL);
	if (size <= tiny / 128)
		block = find_in_heap(size, tiny + sizeof(t_heap));
	else
		block = find_in_heap(size, small + sizeof(t_heap));
	return (block);
}

void	*run_malloc(size_t size)
{
	t_block			*block;
	struct rlimit	limit;

	block = NULL;
	if (size <= 0)
		return (NULL);
	if (getrlimit(RLIMIT_DATA, &limit) < 0)
		return (NULL);
	if (size + sizeof(t_heap) > limit.rlim_max)
		return (NULL);
	block = find_available_block(size);
	if (block == NULL)
		block = allocate_new_heap(size);
	if (!block)
		return (NULL);
	return (block->start_data);
}

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex_malloc);
	ptr = run_malloc(size);
	pthread_mutex_unlock(&g_mutex_malloc);
	return (ptr);
}
