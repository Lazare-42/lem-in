/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:27:56 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/14 13:33:49 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <unistd.h>
//unistd is for sleep / chechking leaks ; take it away when done

const char	*set_get_end_name(const char *name)
{
	static const char	*storage = NULL;

	if (name)
		storage = name;
	return (storage);
}

const char	*set_get_start_name(const char *name)
{
	static const char	*storage = NULL;

	if (name)
		storage = name;
	return (storage);
}

t_info	store_node_handler(t_info info, t_node new_node)
{
	if (new_node.number >= info.size)
	{
		info.size *= 2;
		info.nodelist = resize_nodelist(info);
		info.hash_table = resize_hashtable(info);
	}
	info.nodelist[info.n] = new_node;
	info.hash_table = hash_insert(info, new_node); 
	if (info.end_begin_room)
	{
		if (info.end_begin_room == END)
			set_get_end_name(new_node.name);
		else
			set_get_start_name(new_node.name);
	}
	info.n++;
	return (info);
}

t_node	node_create(char *buf, int node_number)
{
	char	**name_and_pos;
	t_node	new_node;


	new_node.number = node_number;
	new_node.weight = NULL;
	new_node.name = NULL;
	new_node.path_marker = NULL;
	name_and_pos = NULL;
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
	int	*tubes;

	i = -1;
	while (++i < info.n)
	{
		tubes = NULL;
		if (!(tubes = malloc(sizeof(int) * info.n)))
			lemin_error("malloc error in create_tubes");
		n = -1;
		while (++n < info.n)
			tubes[n] = 0;
		info.nodelist[i].tubes = tubes;
	}
	return (info);
}

t_info	tube_assign(char *buf, t_info info)
{
	t_node	tube_1;
	t_node	tube_2;
	char	**tubes;

	tubes	= NULL;
	if (!(tubes = ft_strsplit(buf, '-')))
		lemin_error("error in ft_strsplit called from tube_assign");
	tube_1 = hash_retrieve(info, tubes[0]);
	tube_2 = hash_retrieve(info, tubes[1]);
	info.nodelist[tube_1.number].tubes[tube_2.number] = 1;
	info.nodelist[tube_2.number].tubes[tube_1.number] = 1;
	ft_tabdel((void***)&tubes);
	return (info);
}
