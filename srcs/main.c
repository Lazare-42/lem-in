/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/10/02 03:44:35 by lazrossi         ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_info			info;
	t_best_paths	best_paths;

	(void)av;
	info.n = 0;
	info.map.lines = NULL;
	info.map.line_nbr = 0;
	info.map.size = FILE_SIZE;
	info.end_begin_room = 0;
	info.tab_size = DATA_INITIAL_SIZE;
	info.ant_nb = 0;
	info.hash_table = create_table(info);
	info.nodelist = create_table(info);
	info = parse_map(info);
	if (!(dijkstra(info.o_mat, info.n)))
		lemin_error("There is no path from start to end");
	get_best_paths(&info, &best_paths, 10);
	output_print(&best_paths, &info, ac == 1 ? PRINT_INPUT : 0);
	return (0);
}
