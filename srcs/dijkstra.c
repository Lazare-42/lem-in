/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:56:02 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/06 00:57:56 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

static void	mat_reset_for_dijkstra(int **mat, int size)
{
	int y;

	mat[1][0] = 0;
	y = 2;
	while (y < size)
	{
		mat[y][0] = 99;
		y++;
	}
}

int			dijkstra(int **mat, int size)
{
	int	*node;
	int	**queue;
	int	x;
	int	weight;
	int	is_path; //DANS L ATTENTE DE LA HEAP UNIQUEMENT

	is_path = 0; //PROVISOIRE
	node = &(mat[1][0]);
	queue = queue_create(size);
	queue_add_elem(queue, node);
	mat_reset_for_dijkstra(mat, size);
	while ((node = queue_pick_last(queue)))
	{
		x = 0;
		weight = *node;
		while (++x < size)
		{
			if (node[x] && weight + node[x] < mat[x][0])
			{
				mat[x][0] = weight + node[x];
				queue_add_elem(queue, &(mat[x][0]));
				if (x == size - 1)
					is_path = 1; // PROVISOIRE
					//return (1);
			}
		}
	}
	free(queue);
	return (is_path);
}
