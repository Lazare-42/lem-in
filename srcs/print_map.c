#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

void	print_rooms(t_info info)
{
	int i;
	i = 0;

	while (info.nodelist[i].name)
	{
		ft_printf("[[~/Documents/42/lem-in/map.txt]]%10s is room name, %d x %d y\n",
				info.nodelist[i].name, info.nodelist[i].x, info.nodelist[i].y);
		i++;
	}
	i = 0;
	t_node *tmp;
	while (i < info.size)
	{
		if (info.hash_table[i].name)
			ft_printf("[[~/Documents/42/lem-in/map_hash.txt]]%10s is room name, %d x %d y\n",
					info.hash_table[i].name, info.hash_table[i].x, info.hash_table[i].y);
		tmp = info.hash_table[i].next;
		while (tmp)
		{
			ft_printf("[[~/Documents/42/lem-in/map_hash.txt]]%10s is room name %d x %d y COLLISION\n", tmp->name, tmp->x, tmp->y);
			tmp = tmp->next;
		}
		i++;
	}
	ft_printf("[[~/Documents/42/lem-in/map_hash.txt]]%d is list size %d is list node numbers\n", info.size, info.n);
	ft_printf("[[~/Documents/42/lem-in/map.txt]]%d is list size %d is list node numbers\n", info.size, info.n);

}

void	print_hash_map(t_info info)
{
	int i;
	t_node *tmp;

	i = -1;
	ft_printf("[[yellow]][[underline]][[bold]]HASHMAP:\n[[end]]");
	while (++i < info.n)
	{
		if (info.hash_table[i].name)
		{
			ft_printf("[[green]]%s[[end]]", info.hash_table[i].name);
			tmp = info.hash_table[i].next;
			while (tmp)
			{
				ft_printf("[[blue]]->[[end]][[green]]%s[[end]]", tmp->name);
				tmp = tmp->next;
			}
			ft_printf("\n");
		}
	}
}

void	print_tubes(t_info info)
{
	int		i;
	int		n;
	int		square;

	i = -1;
	ft_printf("[[underline]][[cyan]]This is the adjacence matrix :[[end]]\n");
	ft_printf("%-12s\n", "Room Name :");
	while (++i < info.n)
	{
		n = -1;
		ft_printf("%-12s", info.nodelist[i].name);
		while (++n < info.n)
		{
			if ((square = info.nodelist[i].tubes[n]) && n != i)
				ft_printf("[[green]][[bold]]%d [[end]]", square);
			else if (n != i)
				ft_printf("[[blue]]%d [[end]]", square);
			else
				ft_printf("[[magenta]]%d [[end]]", square);
		}
		ft_printf("\n");
	}
}

void	print_map(t_info info, int to_print)
{
	if (to_print == 1)
		print_rooms(info);
	else
		print_tubes(info);
}
