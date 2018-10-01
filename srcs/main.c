/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/10/01 11:37:29 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <math.h>
//unistd is for sleep / chechking leaks ; take it away when done

t_info	comment_mannagement(char *buf, t_info info)
{
	if (ft_memcmp(buf, "##end", 5) && ft_memcmp(buf, "##start", 7))
	{
		(void)buf;
	// Attention : you need to strdup buf if you want to use the commentary
	}
	if (ft_strequ(buf, "##end"))
		info.end_begin_room = END;
	else if (ft_strequ(buf, "##start"))
		info.end_begin_room = START;
	return (info);
}

int		main()
{
	t_info	info;
	t_best_paths	best_paths;

	info.n = 0;
	info.map.to_print = NULL;
	info.map.size = INITIAL_MAP_SIZE;
	info.map.line_nbr = 0;
	info.end_begin_room = 0;
	info.tab_size = DATA_INITIAL_SIZE;
	info.ant_nb = 0;
	info.hash_table = create_table(info);
	info.nodelist = create_table(info);
	info = parse_map(info);
	get_best_paths(&info, &best_paths,  10);
	unsigned int i = 0;
	while (i < info.map.size)
	{
		ft_printf("%s\n", info.map.to_print[i]);
		i++;
	}
//	output_print(&best_paths, &info);
	return (1);
}
