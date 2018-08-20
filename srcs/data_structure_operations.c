#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

static void	old_hashtable_memdel(t_info info, t_node **old_hashtable)
{
	int		i;
	t_node	*tmp;
	t_node	*to_del;

	i = -1;
	while (++i < info.tab_size / 2)
	{
		tmp = (*old_hashtable)[i].next;
		while (tmp)
		{
			to_del = tmp;
			tmp = tmp->next;
			ft_memdel((void**)&to_del);
		}
	}
	ft_memdel((void**)old_hashtable);
}

t_node		*collisioned_node_reinsertion(t_node *collisioned_node,
		t_node *new_hashtable, t_info info)
{
	t_node	*tmp;

	while (collisioned_node)
	{
		tmp = collisioned_node->next;
		collisioned_node->next = NULL;
		new_hashtable = hash_insert(info, *collisioned_node); 
		ft_memdel((void**)&collisioned_node);
		collisioned_node = tmp;
	}
	return (new_hashtable);
}

t_node		*resize_hashtable(t_info info)
{
	int		i;
	t_node	*collisioned_node;
	t_node	*new_hashtable;
	t_node	*old_hashtable;

	i = -1;
	old_hashtable = info.hash_table;
	new_hashtable = create_table(info);
	info.hash_table = new_hashtable;
	while (++i < info.tab_size / 2)
	{
		if (old_hashtable[i].name)
		{
			collisioned_node = old_hashtable[i].next;
			old_hashtable[i].next = NULL;
			new_hashtable = hash_insert(info, old_hashtable[i]); 
			if (collisioned_node)
				collisioned_node_reinsertion
				(collisioned_node, new_hashtable, info);
		}
	}
	old_hashtable_memdel(info, &old_hashtable);
	return (new_hashtable);
}

t_node	*resize_nodelist(t_info info)
{
	t_node	*new_nodelist;
	int		i;
	t_node	void_node;

	i = -1;
	void_node.name = NULL;
	new_nodelist = create_table(info);
	while (++i < info.tab_size / 2)
		new_nodelist[i] = info.nodelist[i];
	while (++i < info.tab_size)
		new_nodelist[i] = void_node;
	ft_memdel((void**)&info.nodelist);
	return (new_nodelist);
}

t_node	*create_table(t_info info)
{
	t_node	*new_nodelist;
	t_node	void_node;
	int		i;

	new_nodelist = NULL;
	void_node.name = NULL;
	void_node.next = NULL;
	if (!(new_nodelist = malloc(sizeof(t_node) * info.tab_size)))
		lemin_error("malloc error in retab_size_nodelist");
	i = -1;
	while (++i < info.tab_size)
		new_nodelist[i] = void_node;
	return (new_nodelist);
}
