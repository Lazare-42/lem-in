/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:33 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/04 16:35:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

static t_info	get_tubes(t_info info, char *buf)
{
	int		ret;

	info = swap_end_begin_room(info, START);
	info = create_tubes(info);
	ret = 1;
	while (ret > 0)
	{
		if (buf[0] == '#')
			info = comment_mannagement(buf, info);
		else
			info = tube_assign(buf, info);
		ft_memdel((void**)&buf);
		ret = get_next_line(0, &buf, '\n');
	}
	return (info);
}

static t_info	get_rooms(t_info info, char *buf)
{
	int		ret;
	int		node_number;

	ret = 1;
	node_number = 0;
	while (ret > 0)
	{
		if (ret > 0 && ft_strchr(buf, '-'))
			return ((get_tubes(info, buf)));
		else if (ret > 0 && buf[0] == '#')
			info = comment_mannagement(buf, info);
		else
		{
			info  = store_node_handler(info, node_create(buf, node_number++));
			info.end_begin_room = 0;
		}
		ft_memdel((void**)&buf);
		ret = get_next_line(0, &buf, '\n');
	}
	lemin_error("no links after room declaration");
	return (info);
}

t_info			parse_map(t_info info)
{
	char	*buf;
	int		ret;

	ret = 1;
	buf = NULL;
	while (ret > 0)
	{
		ret = get_next_line(0, &buf, '\n');
		if (ret <= 0)
			lemin_error("void_map");
		if (buf[0] == '#')
			info = comment_mannagement(buf, info);
		if (!info.ant_nbr)
		{
			if (!(info.ant_nbr = ft_atoi(buf)))
				lemin_error("No ants");
		}
		else if (info.ant_nbr)
		{
			info = get_rooms(info, buf);
			return (info);
		}
		ft_memdel((void**)&buf);
	}
	return (info);
}
