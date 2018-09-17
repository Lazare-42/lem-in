/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/17 02:40:18 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
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

	printf("\nBEFORE1\n");
	info.n = 0;
	info.end_begin_room = 0;
	info.tab_size = DATA_INITIAL_SIZE;
	info.ant_nb = 0;
	info.hash_table = create_table(info);
	info.nodelist = create_table(info);
	info = parse_map(info);
	mat_print(info.o_mat, info.n + 1);
	printf("\nBEFORE2\n");
	best_paths = get_best_paths(&info, 3);
	printf("\nBEST SET OF PATHS : %.1f time\n", best_paths.time); plst_print(&(best_paths.plst));
	print_map(info, 2);
	/* !! */
//	print_hash_map(info);
//	print_map(info, 0);
//	sleep(130);
	/* !! */
	return (1);
}
