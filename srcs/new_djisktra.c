/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djisktra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:13:28 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/20 20:03:58 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

int		***malloc_path_marker(t_info info)
{
	int		***marker;
	int		i;

	if (!(marker = malloc(sizeof(int **) * info.n)))
		lemin_error("malloc error in malloc_path_marker");
	i = -1;
	while (++i < info.n)
	{
		if (!(marker[i] = malloc(sizeof(int *) * 2)))
			lemin_error("malloc error in malloc_path_marker");
		if (!(marker[i][0] = malloc(sizeof(int))))
			lemin_error("malloc error in malloc_path_marker");
		marker[i][1] = NULL;
	}
	return (marker);
}

t_info	mark_next_elem(t_info info, t_path path)
{
	int	n;

	if (info.nodelist[path.node].weight[0] > path.weight_number)
	{
		info.nodelist[path.node].weight[0] = path.weight_number;
		if (!info.nodelist[path.node].path_marker)
			info.nodelist[path.node].path_marker = malloc_path_marker(info);
		info.nodelist[path.node].path_marker[0][0][0] = path.node_from;
		if (path.node == info.n - 1)
			return (info);
		path.weight_number++;
		n = -1;
		while (++n < info.n)
		{
			if (info.nodelist[path.node].tubes[n])
			{
				debug();
				path.node_from = path.node;
				path.node = n;
				info = (mark_next_elem(info, path));
			}
		}
	}
	return (info);
}

t_info	djisktra(t_info info)
{
	int		i;
	int		path_node;
	t_path	path;

	i = 0;
	path_node = NO_PATH;
	while (i < info.n)
	{
		path.node_from = 0;
		path.weight_number = 0;
		if (info.nodelist[0].tubes[i])
		{
			path.node = i;
			info = mark_next_elem(info, path);
		}
		i++;
	}
	if (!(info.nodelist[info.n - 1].path_marker))
		ft_printf("NO_PATH\n");
	else
	{
		info.shortest_path = 2;
		ft_printf("[%s]->", info.nodelist[info.n - 1].name); 
		path_node = info.nodelist[info.n - 1].path_marker[0][0][0];
		while (path_node != 0)
		{
			ft_printf("[%s]", info.nodelist[path_node].name); 
			path_node = info.nodelist[path_node].path_marker[0][0][0];
			ft_printf("->"); 
			info.shortest_path++;
		}
		ft_printf("[%s]\n", info.nodelist[0].name); 
		ft_printf("The shortest path_node length is : %d. The ant number is %d. This makes up for a travel time of %d\n", info.shortest_path, info.ant_nbr, info.shortest_path - 1 + info.ant_nbr - 1);
	}
	return (info);
}
