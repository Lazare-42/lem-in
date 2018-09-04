/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/04 21:18:27 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

t_info	comment_mannagement(char *buf, t_info info)
{
	if (ft_memcmp(buf, "##end", 5) && ft_memcmp(buf, "##start", 7))
		(void)buf;
	if (ft_strequ(buf, "##end"))
		info.end_begin_room = END;
	else if (ft_strequ(buf, "##start"))
		info.end_begin_room = START;
	return (info);
}

int		main(int argc, char **argv)
{
	t_info			info;
	t_map_creator	map_creator_info;

	if (argc > 2)
	{
		map_creator_info.is_valide = 1;
		map_creator_info.type = std;
		map_creator_info.node_nb = ft_atoi(argv[2]);
		map_creator_info.links_percent = ft_atoi(argv[3]);
		map_creator(map_creator_info, argv[1]);
		return (0);
	}
	info.n = 0;
	info.end_begin_room = 0;
	info.tab_size = DATA_INITIAL_SIZE;
	info.ant_nbr = 0;
	info.hash_table = create_table(info);
	info.nodelist = create_table(info);
	info = parse_map(info);
	print_map_visualizer(info, argv[1]);
	return (0);
}
