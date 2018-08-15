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

t_node	*store_node_list(t_info info, t_node new_node)
{
	int		i;

	i = 0;
	while (info.nodelist[i].name != NULL)
		i++;
	info.nodelist[i] = new_node;
	return (info.nodelist);
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
	info.n++;
	return (info);
}

t_node	node_create(char *buf, int node_number)
{
	char	**name_and_pos;
	t_node	new_node;


	name_and_pos = NULL;
	new_node.next = NULL;
	new_node.number = node_number;
	if (!(name_and_pos = ft_split_whitespaces(buf)))
		lemin_error("error in split whitespaces in node_create");
	new_node.name = name_and_pos[0];
	new_node.x = ft_atoi(name_and_pos[1]);
	new_node.y = ft_atoi(name_and_pos[2]);
	ft_memdel((void**)&name_and_pos[1]);
	ft_memdel((void**)&name_and_pos[2]);
	// does buf leak here ?
	return (new_node);
}
