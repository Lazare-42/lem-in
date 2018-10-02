/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 01:52:17 by lazrossi          #+#    #+#             */
/*   Updated: 2018/10/02 02:15:26 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

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

void			update_best_paths(t_best_paths *best_paths, t_plst *new_plst,
		float new_time)
{
	if (new_time < best_paths->time)
	{
		plstdel(&(best_paths->plst));
		best_paths->plst = new_plst;
		best_paths->time = new_time;
	}
	else
		plstdel(&new_plst);
}

int				add_path_if_usefull(float ant_nb, t_paths_info *p_info,
		t_lst_g *lst_g)
{
	float	new_time;
	int		better_path_found;

	better_path_found = 0;
	new_time = (ant_nb + p_info->paths_total_len - p_info->paths_nb)
		/ p_info->paths_nb;
	if (new_time < p_info->time)
	{
		p_info->time = new_time;
		lst_g->tmp_plst->path = lst_g->new_ilst;
		plstadd(&(lst_g->new_plst), lst_g->tmp_plst);
		better_path_found = 1;
	}
	else
		ilstdel(&(lst_g->new_ilst));
	return (better_path_found);
}

void			p_info_init(t_paths_info *p_info)
{
	p_info->paths_total_len = 0;
	p_info->paths_nb = 0;
	p_info->time = INT_MAX;
}
