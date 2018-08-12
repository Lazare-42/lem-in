
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
		pos = (HASH_MULTIPLIER * pos) + *string;
		string++;
	}
	return (pos);
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

void			hash_insert(t_hash_elem **table, const char *name, int size)
{
	int			hash_key;
	t_hash_elem	**tmp_table;
	t_hash_elem	*new;

	tmp_table = table;
	new = NULL;
	hash_key = hashtable_key(name) % size;
	if (tmp_table[hash_key]->name)
	{
		while (tmp_table[hash_key]->next)
			tmp_table[hash_key] = tmp_table[hash_key]->next;
		if (!(new = malloc(sizeof(t_hash_elem))))
			lemin_error("malloc error in hash_insert");
		new->name = name;
		new->next = NULL;
		tmp_table[hash_key]->next = new;
	}
	else
		tmp_table[hash_key]->name = name;
}

void			move_old_table_to_new(t_hash_table *table, t_hash_elem **new_hashtable, int new_size)
{
	int		i;

	i = 0;
	while (i < table->size)
	{
		while (table->hash_table[i])
		{
			hash_insert(new_hashtable, table->hash_table[i]->name, new_size);
			table->hash_table[i] = table->hash_table[i]->next;
		}
		i++;
	}
}

t_hash_table	*create_resize_table(t_hash_table	*table, int size)
{
	t_hash_elem		**new_hashtable;
	int				i;

	new_hashtable = NULL;
	i = -1;
	if (!(new_hashtable = malloc(sizeof(t_hash_elem *) * size)))
		lemin_error("malloc error in create_resize_table");
	while (++i < size)
	{
		if (!(new_hashtable[i] = malloc(sizeof(t_hash_elem))))
			lemin_error("malloc error in create_resize_table");
		new_hashtable[i]->next = NULL;
		new_hashtable[i]->name = NULL;
	}
	if (table->hash_table)
	{
		move_old_table_to_new(table, new_hashtable, size);
		ft_memdel((void**)table->hash_table);
	}
	table->hash_table = new_hashtable;
	return (table);
}
