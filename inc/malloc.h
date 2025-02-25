/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:03:10 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 16:43:33 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H

# define MALLOC_H

# include <pthread.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <string.h>
# include "../libft/libft.h"

extern pthread_mutex_t	g_mutex_malloc;

typedef struct s_block
{
	struct s_block	*prev;
	void			*start;
	void			*start_data;
	int				is_free;
	size_t			data_size;
	size_t			total_size;
	struct s_block	*next;
}		t_block;

typedef struct s_heap
{
	struct s_heap	*prev;
	size_t			heap_size;
	size_t			used_size;
	size_t			free_size;
	size_t			block_used;
	void			*start;
	void			*start_data;
	struct s_block	*first_block;
	struct s_heap	*next;
}					t_heap;

extern t_heap			*g_heap;

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
t_block	*divide_block(t_heap **heap, t_block **block, size_t size);
t_block	*allocate_new_heap(size_t size);
t_block	*new_block(t_heap **heap, void *start, size_t size);
size_t	get_alloc_size(size_t size);
void	ft_itoa_base(size_t n, char *base_to);
void	print_addr(char *log, void *addr);
void	print_bytes(char *log, size_t nbr);
void	print_mem(void *addr);
void	print_s(char *s);
int		is_last_heap(t_heap **heap);
int		is_last_block(t_block **block);
void	replace_first_block(t_heap **heap);
void	replace_g_heap(void);
void	*run_malloc(size_t size);
void	run_free(void *ptr);
void	merge_end_to_free(t_block **block, size_t size, size_t size_dif);
void	show_alloc_mem(void);
void	merge_blocks(t_block **block);
void	merge_end(t_heap **heap, t_block **block);
t_block	*find_in_heap(size_t size, size_t heap_size);
t_block	*get_ptr_in_heap(void *ptr);

#endif
