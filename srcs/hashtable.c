/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 15:54:19 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/13 01:38:58 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

int		hashtable_key(const char *name)
{
	unsigned const char *string;
	int					pos;

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

void			hash_insert(t_node *table, int size, t_node new_node)
{
	int			hash_key;
	t_node		*tmp_table;
	t_node		tmp;

	tmp_table = table;
	hash_key = hashtable_key(new_node.name) % size;
	if (tmp_table[hash_key].name)
	{
		tmp = tmp_table[hash_key];
		while (tmp_table[hash_key].next)
			tmp = *((t_node*)tmp_table[hash_key].next);
		tmp_table[hash_key].next = &new_node;
		return ;
	}
	tmp_table[hash_key] = new_node;
}

t_node		hash_retrieve(t_node *table, const char *name, int size)
{
	int		hash_key;
	t_node	tmp;

	hash_key = hashtable_key(name) % size;
	tmp = table[hash_key];
	if (ft_strcmp(name, table[hash_key].name))
	{
		while (ft_strcmp(name, tmp.name))
			tmp = *((t_node*)table[hash_key].next);
	}
	return (tmp);
}

t_hash_table	*create_table(void)
{
	t_hash_table	*new;

	new = NULL;
	if (!(new = malloc(sizeof(t_hash_table))))
		lemin_error("malloc error in create_table");
	new->hash_table = NULL;
	new->n = 0;
	new->size = 0;
	return (new);
}

/*
void			move_old_table_to_new(t_hash_table *table, t_node *new_hashtable, int new_size)
{
	int		i;

	i = 0;
	while (i < table->size)
	{
		while (table->hash_table[i])
		{
			hash_insert(new_hashtable, new_size, table->hash_table[i]->name, table->hash_table[i]->number);
			table->hash_table[i] = table->hash_table[i]->next;
		}
		i++;
	}
}
*/

t_hash_table	*create_resize_hashtable(t_hash_table	*table, int size)
{
	t_node			*new_hashtable;
	int				i;
	t_node			void_node;

	new_hashtable = NULL;
	i = -1;
	void_node.name = NULL;
	if (!(new_hashtable = malloc(sizeof(t_node) * size)))
		lemin_error("malloc error in create_resize_table");
	while (++i < size)
		new_hashtable[i] = void_node;
	/*
	if (table->hash_table)
	{
		move_old_table_to_new(table, new_hashtable, size);
		ft_memdel((void**)table->hash_table);
	}
	*/
	table->size = size;
	table->hash_table = new_hashtable;
	return (table);
}
