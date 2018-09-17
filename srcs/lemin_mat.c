/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:41 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/17 02:39:46 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

static	int		w_get_next(int **tmp_mat, int **working_mat, int size, int	current_index)
{
	int	x;
	int	lighter_weight;
	int	lighter_node_index;
	int	weight;

	(void)working_mat;

	x = 1;
	lighter_weight = 99;
	lighter_node_index = size - 2;
	//printf("current node index = %c\n", current_index + 65);
	//getchar();
	if (current_index == 0)
		return (-1);
	while (x < size)
	{
		if ((tmp_mat[current_index + 1][x] > 0 || tmp_mat[x][current_index + 1] == -1) && (weight = tmp_mat[x][0]) < lighter_weight)
		{
			lighter_weight = weight;
			lighter_node_index = x;
		}
		x++;
	}
	return (lighter_node_index - 1);
}

int		mat_del_joint_path(int **tmp_mat, int **working_mat, int size)
{
	int y;
	int x;
	int	path_deleted;

	path_deleted = 0;
	y = 1;
	while (y < size)
	{
		x = y;
		while (x < size)
		{
			if (working_mat[y][x] > 0 && working_mat[x][y] > 0)
			{
				path_deleted = 1;
				tmp_mat[y][x] = 0;
				tmp_mat[x][y] = 0;
			}
			x++;
		}
		y++;
	}
	return (path_deleted);
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

	ft_printf("w mat add enter\n");
	while (dijkstra(tmp_mat, n + 1))
	{
		ft_printf("w mat add enter loop 1\n");
		prev_node_index = n - 1;
		while ((next_node_index = w_get_next(tmp_mat, working_mat, n + 1, prev_node_index)) >= 0)
		{
			mat_print(tmp_mat, n + 1);
			mat_print(working_mat, n + 1);
			ft_printf("w mat add enter loop 2\nprev_mode_index = %c\nnext_node_index = %c\n", prev_node_index + 65, next_node_index + 65);
			getchar();
			//mat_del_link(tmp_mat, prev_node_index, next_node_index);
			mat_del_node(tmp_mat, working_mat, n, prev_node_index);
			working_mat[next_node_index + 1][prev_node_index + 1] = BIG;
			working_mat[0][prev_node_index + 1] += 1;
			prev_node_index = next_node_index;
			mat_print(working_mat, n + 1);
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
			if (working_mat[y][x] > 0)
			{
				tmp_mat[y][x] = 0;
				tmp_mat[x][y] = -1;
			}
			x++;
		}
		y++;
	}
}
