/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:00:14 by jboursal          #+#    #+#             */
/*   Updated: 2018/10/02 02:16:25 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void		save_paths_from_mat_if_better_loop(t_info *info, t_lst_g *lst_g,
		t_node_mem *n_mem, t_paths_info *p_info)
{
	n_mem->prev_node_i = info->n - 1;
	lst_g->new_ilst = ilstnew(info->n - 1);
	lst_g->tmp_plst = plstnew(lst_g->new_ilst);
	p_info->paths_nb++;
	while ((n_mem->next_node_i = get_next(info->tmp_mat, info->n + 1,
		lst_g->new_ilst->n)) >= 0 && ++(lst_g->tmp_plst->path_len)
		&& ++(p_info->paths_total_len))
	{
		if (n_mem->prev_node_i + 1 != info->n)
			mat_del_node(info->tmp_mat, info->working_mat,
					info->n + 1, n_mem->prev_node_i);
		else
			mat_del_links(info->tmp_mat, info->working_mat,
			n_mem->prev_node_i + 1, n_mem->next_node_i + 1);
		info->working_mat[n_mem->next_node_i + 1]
		[n_mem->prev_node_i + 1] = info->tmp_mat[n_mem->prev_node_i + 1][0];
		info->working_mat[0][n_mem->prev_node_i + 1] += 1;
		n_mem->prev_node_i = n_mem->next_node_i;
		lst_g->tmp_ilst = ilstnew(n_mem->next_node_i);
		ilstadd(&(lst_g->new_ilst), lst_g->tmp_ilst);
	}
}

void		save_paths_from_mat_if_better(t_info *info,
	t_best_paths *best_paths)
{
	t_lst_g			lst_g;
	t_node_mem		n_mem;
	t_paths_info	p_info;

	lst_g.new_plst = plstnew(0);
	p_info_init(&p_info);
	while (dijkstra(info->tmp_mat, info->n + 1))
	{
		save_paths_from_mat_if_better_loop(info, &lst_g, &n_mem, &p_info);
		if (0 == (add_path_if_usefull(info->ant_nb, &p_info, &lst_g)))
			break ;
	}
	update_best_paths(best_paths, lst_g.new_plst, p_info.time);
}

void		mat_del_last_conflict(int **tmp_mat, int **working_mat, int n)
{
	t_conflict	conflict;
	t_point		coord;
	int			is_conflict;

	conflict.node_1 = 0;
	conflict.node_2 = 0;
	conflict.distance_from_a = 0;
	is_conflict = 0;
	coord.x = 0;
	while (++coord.x < n - 1)
		if (working_mat[0][coord.x] >= 2)
		{
			coord.y = 0;
			is_conflict = 1;
			while (++coord.y < (n - 1))
				if (working_mat[coord.y][coord.x] > conflict.distance_from_a
						&& working_mat[coord.y][coord.x] != BIG)
				{
					conflict.distance_from_a = working_mat[coord.y][coord.x];
					conflict.node_1 = coord.y;
					conflict.node_2 = coord.x;
				}
		}
	tmp_mat[conflict.node_1][conflict.node_2] = 0;
	tmp_mat[conflict.node_2][conflict.node_1] = 0;
}

void		mat_put_reversed_path(int **tmp_mat, int **working_mat, int n)
{
	int	y;
	int	x;

	y = 1;
	while (y < n)
	{
		x = 1;
		while (x < n)
		{
			if (working_mat[y][x] != 0)
			{
				tmp_mat[y][x] = 1;
				tmp_mat[x][y] = 1;
			}
			x++;
		}
		y++;
	}
}

void		get_best_paths(t_info *info, t_best_paths *best_paths, int it_nb)
{
	int				i;

	info->tmp_mat = mat_init(info->n + 1);
	info->working_mat = mat_init(info->n + 1);
	best_paths->time = INT_MAX;
	best_paths->plst = NULL;
	i = 0;
	mat_cpy(info->tmp_mat, info->o_mat, info->n + 1);
	while (i < it_nb)
	{
		mat_put_reversed_path(info->tmp_mat, info->working_mat, info->n + 1);
		if (!(mat_del_joint_path(info->tmp_mat, info->working_mat, info->n)))
			mat_del_last_conflict(info->tmp_mat, info->working_mat, info->n);
		mat_reset(info->working_mat, info->n);
		save_paths_from_mat_if_better(info, best_paths);
		mat_put_reversed_path(info->tmp_mat, info->working_mat, info->n + 1);
		mat_reverse_used_paths(info->tmp_mat, info->working_mat, info->n + 1);
		working_mat_add_new_paths(info->working_mat, info->tmp_mat, info->n);
		i++;
	}
}
