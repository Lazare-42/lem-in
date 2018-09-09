/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 22:34:22 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/09 21:21:04 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	l_heap_del(int ***heap)
{
	free((*heap)[0]);
	free(*heap);
}

void	l_heap_print(int **heap)
{
	int	i;

	i = 1;
	printf("\033[31mHEAP - len %d\n\033[0m", heap[0][0]);
	while (i < heap[0][0] + 1)
	{
		printf(" %03d | node add : %03x | node weight : %03d\n", i,
			(int)heap[i], heap[i][0]);
		i++;
	}
}

int		**l_heap_create(int n)
{
	static int	**heap = 0;
	int			i;
	int			*first;

	if (heap == 0)
	{
		if (!(first = (int*)malloc(sizeof(int) * 1)))
			return (0);
		if (!(heap = (int **)malloc(sizeof(int *) * (n + 1))))
			return (0);
		heap[0] = first;
		heap[0][0] = 0;
		i = 1;
		while (i < n)
		{
			heap[i] = 0;
			i++;
		}
	}
	return (heap);
}

void	l_heap_add(int **heap, int *node)
{
	int		i;
	int		*tmp;

	heap[0][0]++;
	i = heap[0][0];
	heap[i] = node;
	while (i > 1 && heap[i][0] < heap[i / 2][0])
	{
		tmp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = tmp;
		i /= 2;
	}
}

int		*l_heap_pick_first(int **heap)
{
	int		i;
	int		*tmp;
	int		*ret;

	i = 1;
	if (!heap[0][0])
		return (0);
	ret = heap[1];
	heap[1] = heap[heap[0][0]--];
	while (i < heap[0][0] && (heap[i][0] > heap[i / 2][0] || heap[i][0]
		> heap[i / 2 + 1][0]))
	{
		tmp = heap[i];
		if (heap[2 * i][0] < heap[2 * i + 1][0])
		{
			heap[i] = heap[2 * i];
			heap[2 * i] = tmp;
			i = 2 * i;
		}
		else
		{
			heap[i] = heap[2 * i + 1];
			heap[2 * i + 1] = tmp;
			i = 2 * i + 1;
		}
	}
	return (ret);
}