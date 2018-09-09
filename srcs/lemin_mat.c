/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:41 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/06 00:30:34 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static	int		w_get_next(int **tmp_mat, int **working_mat, int size, int	current_index)
{
	int	x;
	int	lighter_weight;
	int	lighter_node_index;
	int	weight;

	x = 1;
	lighter_weight = 99;
	lighter_node_index = size - 2;
	//printf("current node index = %c\n", current_index + 65);
	//getchar();
	if (current_index == 0)
		return (-1);
	while (x < size)
	{
		if ((tmp_mat[current_index + 1][x] > 0 || working_mat[current_index + 1][x]) && (weight = tmp_mat[x][0]) < lighter_weight)
		{
			lighter_weight = weight;
			lighter_node_index = x;
		}
		x++;
	}
	return (lighter_node_index - 1);
}

void	mat_del_joint_path(int **tmp_mat, int **working_mat, int size)
{
	int y;
	int x;

	y = 1;
	while (y < size)
	{
		x = y;
		while (x < size)
		{
			if (working_mat[y][x] && working_mat[x][y])
			{
				tmp_mat[y][x] = 0;
				tmp_mat[x][y] = 0;
			}
			x++;
		}
		y++;
	}
}

void	mat_del_link(int **tmp_mat, int prev_node_index, int next_node_index)
{
	tmp_mat[prev_node_index + 1][next_node_index + 1] = 0;
	tmp_mat[next_node_index + 1][prev_node_index + 1] = 0;
}

void	working_mat_add_new_paths(int **working_mat, int **tmp_mat, int n)
{
	int		next_node_index;
	int		prev_node_index;

	while (dijkstra(tmp_mat, n + 1))
	{
		prev_node_index = n - 1;
		while ((next_node_index = w_get_next(tmp_mat, working_mat, n + 1, prev_node_index)) >= 0)
		{
			mat_del_link(tmp_mat, prev_node_index, next_node_index);
			working_mat[next_node_index + 1][prev_node_index + 1] = 1;
			prev_node_index = next_node_index;
		}
	}
}

void	mat_reverse_used_paths(int **tmp_mat, int **working_mat, int size)
{
	int y;
	int x;

	y = 1;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (working_mat[y][x])
			{
				tmp_mat[y][x] = 0;
				tmp_mat[x][y] = -1;
			}
			x++;
		}
		y++;
	}
}