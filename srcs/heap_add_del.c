/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_add_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 02:27:06 by lazrossi          #+#    #+#             */
/*   Updated: 2018/10/02 02:42:03 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	l_heap_del(int ***heap)
{
	free((*heap)[0]);
	free(*heap);
}

void	l_heap_add(int **heap, int *node)
{
	int		i;
	int		*tmp;

	heap[0][0]++;
	if ((i = l_heap_chrnul(heap, node)) != heap[0][0])
		heap[0][0]--;
	heap[i] = node;
	while (i > 1 && heap[i][0] < heap[i / 2][0])
	{
		tmp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = tmp;
		i /= 2;
	}
}
