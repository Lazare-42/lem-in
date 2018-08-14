#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_node		*resize_hashtable(t_info info)
{
	int		i;
	t_node	*collisioned_node;
	t_node	*new_hashtable;
	t_node	*old_hashtable;

	i = -1;
	old_hashtable = info.hash_table;
	new_hashtable = create_hashtable(info);
	info.hash_table = new_hashtable;
	while (++i < info.size / 2)
	{
		if (old_hashtable[i].name)
		{
			new_hashtable = hash_insert(info, old_hashtable[i]); 
			collisioned_node = old_hashtable[i].next;
			while (collisioned_node)
			{
				new_hashtable = hash_insert(info, *collisioned_node); 
				collisioned_node = collisioned_node->next;
			}
		}
	}
	ft_memdel((void**)&(old_hashtable));
	return (new_hashtable);
}

t_node		*create_hashtable(t_info info)
{
	t_node			*new_hashtable;
	int				i;
	t_node			void_node;

	i = -1;
	new_hashtable = NULL;
	void_node.name = NULL;
	void_node.next = NULL;
	if (!(new_hashtable = malloc(sizeof(t_node) * info.size)))
		lemin_error("malloc error in create_resize_table");
	while (++i < info.size)
		new_hashtable[i] = void_node;
	return (new_hashtable);
}

t_node	*resize_nodelist(t_info info)
{
	t_node	*new_nodelist;
	int		i;
	t_node	void_node;

	i = -1;
	void_node.name = NULL;
	new_nodelist = create_nodelist(info);
	while (++i < info.size / 2)
		new_nodelist[i] = info.nodelist[i];
	while (++i < info.size)
		new_nodelist[i] = void_node;
	ft_memdel((void**)&info.nodelist);
	return (new_nodelist);
}

t_node	*create_nodelist(t_info info)
{
	t_node	*new_nodelist;
	t_node	void_node;
	int		i;

	new_nodelist = NULL;
	void_node.name = NULL;
	if (!(new_nodelist = malloc(sizeof(t_node) * info.size)))
		lemin_error("malloc error in resize_nodelist");
	i = 0;
	while (i < info.size)
	{
		new_nodelist[i] = void_node;
		i++;
	}
	return (new_nodelist);
}
