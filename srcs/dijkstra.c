/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:56:02 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/30 00:06:55 by jboursal         ###   ########.fr       */
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
/*
#include <stdio.h>

static void		node_print(int *node, int size)
{
	printf("node add : %03x\n", (int)node); fflush(stdout);
	printf("X ");
	int i = 0;
	while (++i < size)
		printf("%c ", i + 64);
	printf("\n");
	i = -1;
	while (++i < size)
		printf("%d ", node[i]); fflush(stdout);
	printf("\n\n");
}
*/
#include <stdio.h>

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
		//printf("plop\n");
		x = 0;
		weight = *node;
		//node_print(node, size);
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
