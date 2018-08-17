/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 15:54:19 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/14 14:35:59 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

int		hashtable_key(const char *name)
{
	unsigned const char *string;
	int					pos;

	if (!name)
		return (0);
	pos = 0;
	string = (unsigned const char *)name;
	while (*string)
	{
		pos = (DATA_MULTIPLIER * pos) + *string;
		string++;
	}
	if (pos < 0)
		pos *= -1;
	return (pos);
}

t_node	*hash_insert(t_info info, t_node new_node)
{
	int		key;
	t_node	*tmp;
	t_node	*new;

	new_node.next = NULL;
	key = hashtable_key(new_node.name) % info.size;
	if (info.hash_table[key].name && ft_strcmp(new_node.name, info.hash_table[key].name))
	{
		tmp = &info.hash_table[key];
		while (tmp->next)
			tmp = tmp->next;
		if (!(new = malloc(sizeof(t_node))))
			lemin_error("malloc error in hash_insert");
		*new = new_node;
		tmp->next = new;
	}
	else
		info.hash_table[key] = new_node;
	return (info.hash_table);
}

t_node		hash_retrieve(t_info info, const char *to_find)
{
	int		hash_key;
	t_node	tmp;

	hash_key = hashtable_key(to_find) % info.size;
	tmp = info.hash_table[hash_key];
	if (!tmp.name)
		lemin_error("incorrect room name passed in tubes");
	if (ft_strcmp(to_find, info.hash_table[hash_key].name))
	{
		while (ft_strcmp(to_find, tmp.name))
			tmp = *((t_node*)info.hash_table[hash_key].next);
	}
	if (!tmp.name)
		lemin_error("incorrect room name passed in tubes");
	return (tmp);
}

t_info		hash_delete_elem(t_info info, const char *to_find)
{
	int		hash_key;
	t_node	simple_node;
	t_node	*malloced_node;

	hash_key = hashtable_key(to_find) % info.size;
	simple_node = info.hash_table[hash_key];
	if (ft_strcmp(to_find, info.hash_table[hash_key].name))
	{
		while (ft_strcmp(to_find, simple_node.name))
		{
			simple_node = *((t_node*)info.hash_table[hash_key].next);
			malloced_node = (t_node*)(info.hash_table[hash_key].next);
		}
		ft_memdel((void**)&malloced_node);
	}
	else
		info.hash_table[hash_key].name = NULL;
	return (info);
}
