/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/13 02:11:35 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	comment_mannagement(char *buf)
{
	(void)buf;
}

t_node	node_create(char *buf, int node_number)
{
	char	**name_and_pos;
	t_node	new_node;


	name_and_pos = NULL;
	if (!(name_and_pos = ft_split_whitespaces(buf)))
		lemin_error("error in split whitespaces in node_create");
	new_node.number = node_number;
	new_node.name = name_and_pos[0];
	new_node.x = ft_atoi(name_and_pos[1]);
	new_node.y = ft_atoi(name_and_pos[2]);
	return (new_node);
}

void	create_resize_nodelist(t_info info)
{
	t_node	*new_nodelist;
	t_node	void_node;
	int		i;
	int		size;
	int		new_size;

	new_nodelist = NULL;
	void_node.name = NULL;
	new_size = (info.nodelist) ? info.size * 2 : info.size;
	if (!(new_nodelist = malloc(sizeof(t_node) * new_size)))
		lemin_error("malloc error in resize_nodelist");
	while (i < new_size)
	{
		if (info.nodelist && i < info.size)
			new_nodelist[i] = info.nodelist[i];
		else
			new_nodelist[i] = void_node;
	}
}

void	store_node(t_node new_node, t_info info)
{
	t_node	*new_nodelist;
	int		i;

	new_nodelist = NULL;
	i = 0;
	hash_insert(info.hash_table->hash_table, info.hash_table->size, new_node); 
	if (!info.nodelist)
		create_resize_nodelist(info);
	if (new_node.number > info.hash_table->size)
	{
		resize_nodelist(info);
	}
	/* BUT WAIT : no need for the second structure ; everything is contained in info
	 * be also careful of when you modify info.size
	if (node_number > info.hash_table->size)
		create_resize_hashtable(info.hash_table, info.hash_table->size * 2);
		*/
}

char	*get_rooms(t_info info, char *buf)
{
	int		ret;
	int		node_number;

	ret = 1;
	ft_memdel((void**)&buf);
	node_number = 0;
	while ((ret = get_next_line(0, &buf, '\n')) > 0)
	{
		if (buf[0] == '#')
		{
			if (ft_strlen(buf) == 5 && !ft_strcmp(buf, "##end"))
			{
				return (buf);
			}
			else if (ft_strlen(buf) >= 2)
				comment_mannagement(buf);
			else
				lemin_error(buf);
		}
		else
			store_node(node_create(buf, node_number++), info);
		ft_memdel((void**)&buf);
		// need to store the last nodes number
	}
	lemin_error("no tubes after room declaration or GNL returned < 1");
	return (NULL);
}

t_info	parse_map()
{
	t_info	info;
	char	*buf;
	int		ret;

	ret = 1;
	info.hash_table = NULL;
	info.nodelist = NULL;
	if (!(info.nodelist = malloc(sizeof(t_node *) * DATA_INITIAL_SIZE)))
		lemin_error("malloc error in parse_map");
	info.hash_table = create_table();
	create_resize_hashtable(info.hash_table, DATA_INITIAL_SIZE);
	while ((ret = get_next_line(0, &buf, '\n')))
	{
		if (ret == -1)
			lemin_error("get_next_line returned -1 in parse_map");
		if (ft_strstr(buf, "##start"))
			buf = get_rooms(info, buf);
		ft_memdel((void**)&buf);
	}
	return (info);
}

int		main()
{
	t_info	info;

	info = parse_map();
	return (1);
}
