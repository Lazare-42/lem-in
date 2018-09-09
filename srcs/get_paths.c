/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:00:14 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/10 00:12:28 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <limits.h>

int				get_paths_total_len(t_plst **plst)
{
	t_plst	*tmp;
	int		len;

	tmp = *plst;
	len = 0;
	while (tmp)
	{
		len += tmp->path_len;
		tmp = tmp->next;
	}
	return (len);
}

int				get_next(int **mat, int size, int current_index)
{
	int	x;
	int	lighter_weight;
	int	lighter_node_index;
	int	weight;

	x = 1;
	lighter_weight = 99;
	lighter_node_index = size - 2;
	if (current_index == 0)
		return (-1);
	while (x < size)
	{
		if (mat[current_index + 1][x] > 0 && (weight = mat[x][0])
			< lighter_weight)
		{
			lighter_weight = weight;
			lighter_node_index = x;
		}
		x++;
	}
	return (lighter_node_index - 1);
}

void			update_best_paths(t_best_paths *best_paths, t_plst *new_plst, /*int ant_nb*/ float new_time)
{
	if (new_time < best_paths->time)
	{
		best_paths->time = new_time;
		plstdel(&(best_paths->plst));
		best_paths->plst = new_plst;
	}
	else
	{
		plstdel(&new_plst);
	}
}

int				add_path_if_usefull(float ant_nb, t_paths_info *p_info, t_lst_g *lst_g)
{
	float	new_time;

	new_time = (ant_nb + p_info->paths_total_len - p_info->paths_nb) / p_info->paths_nb;
	if (new_time <  p_info->time)
	{
		p_info->time = new_time;
		lst_g->tmp_plst->path = lst_g->new_ilst;
		plstadd(&(lst_g->new_plst), lst_g->tmp_plst);
		return (1);
	}
	//else
	//	ilstdel(&(lst_g->new_ilst));
	return (0);
}

void			p_info_init(t_paths_info *p_info)
{
	p_info->paths_total_len = 0;
	p_info->paths_nb = 0;
	p_info->time = INT_MAX;
}

void			save_paths_from_mat_if_better(t_info *info,
	t_best_paths *best_paths)
{
	t_lst_g			lst_g;
	t_node_mem		n_mem;
	t_paths_info	p_info;

	lst_g.new_plst = plstnew(0);
	p_info_init(&p_info);
	while (dijkstra(info->tmp_mat, info->n + 1))
	{
		n_mem.prev_node_i = info->n - 1;
		lst_g.new_ilst = ilstnew(info->n - 1);
		lst_g.tmp_plst = plstnew(lst_g.new_ilst);
		p_info.paths_nb++;
		while ((n_mem.next_node_i = get_next(info->tmp_mat, info->n + 1,
			lst_g.new_ilst->n)) >= 0 && ++(lst_g.tmp_plst->path_len) && ++p_info.paths_total_len)
		{
			mat_del_link(info->tmp_mat, n_mem.prev_node_i, n_mem.next_node_i);
			info->working_mat[n_mem.next_node_i + 1][n_mem.prev_node_i + 1] = 1;
			n_mem.prev_node_i = n_mem.next_node_i;
			lst_g.tmp_ilst = ilstnew(n_mem.next_node_i);
			ilstadd(&(lst_g.new_ilst), lst_g.tmp_ilst);
		}
		if (!(add_path_if_usefull(info->ant_nb, &p_info, &lst_g)))
			break;
	}
	update_best_paths(best_paths, lst_g.new_plst, p_info.time);
}

t_best_paths	get_best_paths(t_info *info, int it_nb)
{
	int				i;
	t_best_paths	best_paths;

	info->tmp_mat = mat_init(info->n + 1);
	info->working_mat = mat_init(info->n + 1);
	best_paths.time = INT_MAX;
	best_paths.plst = plstnew(0);
	i = 0;
	while (i < it_nb)
	{
		mat_cpy(info->tmp_mat, info->o_mat, info->n + 1);
		mat_del_joint_path(info->tmp_mat, info->working_mat, info->n);
		mat_reset(info->working_mat, info->n);
		save_paths_from_mat_if_better(info, &best_paths);
		mat_cpy(info->tmp_mat, info->o_mat, info->n + 1);
		mat_reverse_used_paths(info->tmp_mat, info->working_mat, info->n + 1);
		working_mat_add_new_paths(info->working_mat, info->tmp_mat, info->n);
		i++;
	}
	return (best_paths);
}
