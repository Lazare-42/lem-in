/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/11 20:11:25 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	comment_mannagement(char *buf)
{
	(void)buf;
}

t_node	*new_node(char *name)
{
	t_node	*new;

	new = NULL;
	if (!(new = malloc(sizeof(t_node))))
		lemin_error("malloc error in create_node");
	new->sizeof_links = 1;
	if (!(new->links = malloc(sizeof(t_node *) * new->sizeof_links)))
		lemin_error("malloc error in create_node");
	new->path_marker = NULL;
	new->links = NULL;
	new->next = NULL;
	new->name = NULL;
	if (!(new->name = ft_strdup(name)))
		lemin_error("malloc error in create_node");
	return (new);
}

t_node		*add_node_to_list(char *name, t_node *first)
{
	t_node	*tmp;
	t_node	*new;

	tmp = first;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = new_node(name);
	if (tmp)
		tmp->next = new;
	else
		first = new;
	return (new);
}

t_node	*find_existing_node(char *name, t_node	*first)
{ 
	t_node	*tmp;
	int		i;

	tmp = first;
	while (tmp)
	{
		i = -1;
		while (tmp->links && tmp->links[++i])
		{
			if (ft_strstr(tmp->links[i]->name, name))
				return (tmp->links[i]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	enlarge_tube_links(t_node *node, t_node *new_node)
{
	int		i;
	t_node	**new_tubes;

	new_tubes = NULL;
	if (!(new_tubes = malloc(sizeof(t_node *) * (node->sizeof_links * 2))))
		lemin_error("malloc error in enlarge_tube_links");
	new_tubes[node->sizeof_links + 1] = NULL;
	i = -1;
	while (++i < node->sizeof_links)
		new_tubes[i] = node->links[i];
	new_tubes[node->sizeof_links] = new_node;
	ft_memdel((void**)node->links);
	node->links = new_tubes;
	node->sizeof_links *= 2;
}

void	add_tube(char *tube_name, t_node *node)
{
	char	*name;

	name = NULL;
	if (!tube_name || !*(tube_name + 1))
		lemin_error("Invalid tube name in add_tube");
	else if (!(name = ft_strdup(tube_name + 1)))
		lemin_error("malloc error in add_tube");
	if (!node->links)
	{
		if (!(node->links = malloc(sizeof(t_node *) * 2)))
			lemin_error("malloc error in add_tube");
		node->links[0] = new_node(tube_name);
		node->links[1] = NULL;
		return ;
	}
	else enlarge_tube_links(name, node);
}

void	add_node(char *buf, t_node *first)
{
	t_node	*tmp;
	char	*name;
	int		i;

	tmp = first;
	name = NULL;
	i = -1;
	ft_printf("[[~/Documents/42/lem-in/debug.txt]] this is buf : %s\n", buf);
	if (!(name = ft_strndup(buf, ft_strchr(buf, '-') - buf)))
		lemin_error("create_node : malloc error or no '-' in buf.");
	if (!(tmp = find_existing_node(name, first)))
		tmp = add_node_to_list(name, first);
	add_tube(ft_strchr(buf, '-'), tmp);
}

t_node	*get_list()
{
	t_node	*linked_list;
	int		ret;
	char	*buf;

	ret = 1;
	buf = NULL;
	linked_list = NULL;
	while ((ret = get_next_line(0, &buf, '\n')))
	{
		if (ret == -1)
			lemin_error("get_next_line returned -1");
		if (buf[0] && buf[1] && buf[0] == '#' && buf[1] == '#')
			comment_mannagement(buf);
		add_node(buf, linked_list); 
	}
	return (linked_list);
}

t_node	*parse_map()
{
	t_node	*linked_list;
	char	*buf;
	int		ret;

	linked_list = NULL;
	ret = 1;
	while ((ret = get_next_line(0, &buf, '\n')))
	{
		if (ret == -1)
			lemin_error("get_next_line returned -1");
		if (ft_strstr(buf, "##end"))
			linked_list = get_list();
		ft_memdel((void**)&buf);
	}
	return (linked_list);
}

int		main()
{
	t_node	*linked_list;

	linked_list = NULL;
	if (!(linked_list = parse_map()))
		lemin_error("parse_map function returned NULL");
	return (1);
}
