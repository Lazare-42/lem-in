/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:27:56 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/28 15:37:40 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_info	store_node_handler(t_info info, t_node new_node)
{
	if (new_node.number >= info.tab_size)
	{
		info.tab_size *= 2;
		info.nodelist = resize_nodelist(info);
		info.hash_table = resize_hashtable(info);
	}
	info.nodelist[info.n] = new_node;
	info.hash_table = hash_insert(info, new_node);
	if (info.end_begin_room)
	{
		if (info.end_begin_room == END)
			info.end_name = new_node.name;
		else
			info.begin_name = new_node.name;
	}
	info.n++;
	return (info);
}

t_node	node_create(char *buf, int node_number)
{
	char	**name_and_pos;
	t_node	new_node;

	new_node.number = node_number;
	new_node.name = NULL;
	name_and_pos = NULL;
	if (buf && !buf[0])
		lemin_error("You passed an empty line in the map");
	if (!(name_and_pos = ft_split_whitespaces(buf)))
		lemin_error("error in split whitespaces in node_create");
	new_node.name = name_and_pos[0];
	new_node.x = ft_atoi(name_and_pos[1]);
	new_node.y = ft_atoi(name_and_pos[2]);
	ft_memdel((void**)&name_and_pos[1]);
	ft_memdel((void**)&name_and_pos[2]);
	ft_memdel((void**)&name_and_pos[3]);
	free(name_and_pos);
	name_and_pos = NULL;
	return (new_node);
}

t_info	create_tubes(t_info info)
{
	int i;
	int	n;
	int	**tubes;

	i = -1;
	tubes = NULL;
	if (!(tubes = malloc(sizeof(int *) * (info.n + 1))))
		lemin_error("malloc error in create_tubes");
	while (++i < info.n + 1)
	{
		tubes[i] = NULL;
		if (!(tubes[i] = malloc(sizeof(int) * (info.n + 1))))
			lemin_error("malloc error in create_tubes");
		n = -1;
		while (++n < info.n + 1)
			tubes[i][n] = 0;
	}
	info.o_mat = tubes;
	return (info);
}

t_info	tube_assign(char *buf, t_info info)
{
	t_node	tube_1;
	t_node	tube_2;
	int		i;
	char	*to_find_1;
	char	*to_find_2;

	to_find_1 = buf;
	i = 0;
	while (buf[i] && buf[i] != '-')
		i++;
	if (buf[i] != '-' || !buf[i])
		lemin_error("error in tube assigning in tube_assign");
	buf[i] = '\0';
	i++;
	to_find_2 = &buf[i];
	tube_1 = hash_retrieve(info, to_find_1);
	tube_2 = hash_retrieve(info, to_find_2);
	if (tube_1.number != tube_2.number)
	{
		info.o_mat[tube_1.number + 1][tube_2.number + 1] = 1;
		info.o_mat[tube_2.number + 1][tube_1.number + 1] = 1;
	}
	return (info);
}
