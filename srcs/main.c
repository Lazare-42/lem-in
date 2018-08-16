/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/13 19:01:28 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <unistd.h>
//unistd is for sleep / chechking leaks ; take it away when done

void	comment_mannagement(char *buf)
{
	// Attention : you need to strdup buf if you want to use the commentary
	if (ft_strlen(buf) >= 2)
		(void)buf;
	else
		lemin_error(buf);
}



int		main()
{
	t_info	info;

	info.n = 0;
	info.size = DATA_INITIAL_SIZE;
	info.hash_table = create_table(info);
	info.nodelist = create_table(info);
	info = parse_map(info);
	print_map(info, 0);
	sleep(30);
	return (1);
}
