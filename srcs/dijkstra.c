/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:56:02 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/30 22:02:29 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <limits.h>

static void	mat_reset_for_dijkstra(int **mat, int size)
{
	int y;

	mat[1][0] = 0;
	y = 2;
	while (y < size)
	{
		mat[y][0] = INT_MAX;
		y++;
	}
}

int			dijkstra(int **mat, int size)
{
	int	*node;
	int	**heap;
	int	x;
	int	weight;

	node = &(mat[1][0]);
	heap = l_heap_create(size);
	l_heap_add(heap, node);
	mat_reset_for_dijkstra(mat, size);
	while ((node = l_heap_pick_first(heap)))
	{
		x = 0;
		weight = *node;
		while (++x < size)
		{
			if (node[x] && weight + node[x] < mat[x][0] && weight + node[x] > 0)
			{
				mat[x][0] = weight + node[x];
				l_heap_add(heap, &(mat[x][0]));
				if (x == size - 1)
					return (1);
			}
		}
	}
	return (0);
}
