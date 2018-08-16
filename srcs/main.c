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

void	comment_mannagement(char *buf)
{
	if (ft_strlen(buf) >= 2)
		(void)buf;
	else
		lemin_error(buf);
}

t_info	get_rooms(t_info info, char *buf)
{
	int		ret;
	int		node_number;

	ret = 1;
	node_number = 0;
	buf = NULL;
	while (ret > 0)
	{
		ft_memdel((void**)&buf);
		ret = get_next_line(0, &buf, '\n');
		if (ft_strchr(buf, '-'))
		{
			ft_memdel((void**)&buf);
			return (info);
		}
		if (buf[0] == '#' && ft_strcmp(buf, "##end"))
			comment_mannagement(buf);
		else if (!ft_memcmp(buf, "##end", 5))
			continue ;
		else
			info  = store_node_handler(info, node_create(buf, node_number++));
	}
	lemin_error("no tubes after room declaration or GNL return was < 1");
	return (info);
}

t_info	parse_map()
{
	t_info	info;
	char	*buf;
	int		ret;

	ret = 1;
	info.n = 0;
	buf = NULL;
	info.size = DATA_INITIAL_SIZE;
	info.hash_table = create_table(info);
	info.nodelist = create_table(info);
	while (ret > 0)
	{
		get_next_line(0, &buf, '\n');
		if (ret == -1)
			lemin_error("get_next_line returned -1 in parse_map");
		if (buf && ft_strstr(buf, "##start"))
		{
			ft_memdel((void**)&buf);
			info = get_rooms(info, buf);
			//	print_map(info);
			ret = 0;
		}
		ft_memdel((void**)&buf);
	}
	return (info);
}

int		main()
{
	t_info	info;

	info = parse_map();
	sleep(30);
	return (1);
}
