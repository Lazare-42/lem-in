/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djisktra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:13:28 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/20 18:04:40 by lazrossi         ###   ########.fr       */
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

t_info	mark_next_elem(t_info info, int i, int weight_number, int node_from)
{
	int	n;

	if (info.nodelist[i].weight[0] > weight_number)
	{
		info.nodelist[i].weight[0] = weight_number;
		if (!info.nodelist[i].path_marker)
			info.nodelist[i].path_marker = malloc_path_marker(info);
		info.nodelist[i].path_marker[0][0][0] = node_from;
		if (i == info.n - 1)
			return (info);
		weight_number++;
		n = -1;
		while (++n < info.n)
		{
			if (info.nodelist[i].tubes[n])
				info = (mark_next_elem(info, n, weight_number, i));
		}
	}
	return (info);
}

t_info	djisktra(t_info info)
{
	int i;
	int	j;
	int	path;

	i = 0;
	j = 0;
	path = NO_PATH;
	while (i < info.n)
	{
		if (info.nodelist[0].tubes[i])
			info = mark_next_elem(info, i, 0, 0);
		i++;
	}
	if (!(info.nodelist[info.n - 1].path_marker))
		ft_printf("NO_PATH");
	else
	{
		info.shortest_path = 2;
		ft_printf("[%s]->", info.nodelist[info.n - 1].name); 
		path = info.nodelist[info.n - 1].path_marker[0][0][0];
		while (path != 0)
		{
			ft_printf("[%s]", info.nodelist[path].name); 
			path = info.nodelist[path].path_marker[0][0][0];
			ft_printf("->"); 
			info.shortest_path++;
		}
		ft_printf("[%s]\n", info.nodelist[0].name); 
		ft_printf("The shortest path length is : %d. This makes up for a travel time of %d\n", info.shortest_path, info.shortest_path - 1 + info.ant_nbr - 1);
	}
	return (info);
}
