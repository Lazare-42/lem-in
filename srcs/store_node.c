#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

static t_node	*store_node_list(t_info info, t_node new_node)
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
	if (new_node.number > info.size)
	{
		info.nodelist = resize_nodelist(info);
		info.hash_table = resize_hashtable(info);
		info.size *= 2;
	}
	info.hash_table = hash_insert(info, new_node); 
	info.nodelist = store_node_list(info, new_node);
	info.n++;
	return (info);
}

t_node	node_create(char *buf, int node_number)
{
	char	**name_and_pos;
	t_node	new_node;


	name_and_pos = NULL;
	if (!(name_and_pos = ft_split_whitespaces(buf)))
		lemin_error("error in split whitespaces in node_create");
	if (!ft_strcmp("##end", buf))
		ft_printf("[[~/Documents/42/lem-in/error_trace.txt]]%s\n", buf);
	new_node.number = node_number;
	new_node.name = name_and_pos[0];
	new_node.x = ft_atoi(name_and_pos[1]);
	new_node.y = ft_atoi(name_and_pos[2]);
	return (new_node);
}
