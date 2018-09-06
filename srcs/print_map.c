/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:39 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/20 15:05:39 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (i < info.tab_size)
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
	ft_printf("[[~/Documents/42/lem-in/map_hash.txt]]%d is list tab_size %d is list node numbers\n", info.tab_size, info.n);
	ft_printf("[[~/Documents/42/lem-in/map.txt]]%d is list tab_size %d is list node numbers\n", info.tab_size, info.n);

}

void	print_hash_map(t_info info)
{
	int i;
	int	null_tab_size;
	int	elem_number;
	t_node *tmp;

	i = -1;
	null_tab_size = 0;
	elem_number = 0;
	ft_printf("[[yellow]][[underline]][[bold]]HASHMAP:\n[[end]]");
	while (++i < info.tab_size)
	{
		if (info.hash_table[i].name)
		{
			if (null_tab_size)
				ft_printf("[[magenta]][null] * % -d\n[[end]]", null_tab_size);
			null_tab_size = 0;
			if ((ft_strcmp(info.hash_table[i].name, (set_get_end_name(NULL))) && ft_strcmp(info.hash_table[i].name, set_get_start_name(NULL))))
				ft_printf("[[green]]%s[[end]]", info.hash_table[i].name);
			else
				ft_printf("[[yellow]]%s[[end]]", info.hash_table[i].name);
			ft_printf("[[italic]]°%-6d[[end]]", info.hash_table[i].number);
			tmp = info.hash_table[i].next;
			elem_number++;
			while (tmp)
			{
				elem_number++;
				if ((ft_strcmp(tmp->name, set_get_end_name(NULL))) && ft_strcmp(tmp->name, set_get_start_name(NULL)))
					ft_printf("[[blue]]->   [[end]][[green]]%s", tmp->name);
				else
					ft_printf("[[blue]]->   [[end]][[yellow]]%s", tmp->name);
				ft_printf("[[end]][[italic]]°%-6d[[end]]", tmp->number);
				tmp = tmp->next;
			}
			ft_printf("\n");
		}
		else
			null_tab_size++;
	}
	ft_printf("[[bold]][[underline]]Total elements[[end]] : [[red]][[italic]]%d\n[[end]]", elem_number);
}

void	print_tubes(t_info info)
{
	int		i;
	int		n;
	int		square;

	i = -1;
	ft_printf("\nAnt number : %d[[end]]\n", info.ant_nb);
	ft_printf("[[underline]][[cyan]]This is the adjacence matrix :[[end]]\n");
	ft_printf("%-12s\n", "Room Name :");
	while (++i < info.n + 1)
	{
		n = -1;
		if (i - 1 >= 0)
			ft_printf("%-12s", info.nodelist[i - 1].name);
		else
			ft_printf("%-12s", NULL);
		while (++n < info.n + 1)
		{
			if ((square = info.o_mat[i][n]) && n != i)
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
