/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 02:14:19 by lazrossi          #+#    #+#             */
/*   Updated: 2018/10/02 02:15:25 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

void			mat_del_links(int **tmp_mat, int **working_mat,
		int node_from, int node_to)
{
	tmp_mat[node_from][node_to] = 0;
	tmp_mat[node_to][node_from] = 0;
	working_mat[node_from][node_to] = -1;
	working_mat[node_to][node_from] = -1;
}

void			mat_del_node(int **tmp_mat, int **working_mat, int n, int node)
{
	int	y;

	if (node + 2 == n)
		return ;
	y = 1;
	while (y < n)
	{
		if (tmp_mat[y][node + 1])
		{
			tmp_mat[y][node + 1] = 0;
			working_mat[y][node + 1] = -1;
		}
		y++;
	}
}
