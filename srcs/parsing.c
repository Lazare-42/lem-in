/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:33 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/28 15:28:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

static void		save_lines(t_info *info, char *buf, int duplicate_or_save)
{
	char		**new_map;
	int			map_counter;

	if (NULL == info->map.lines || info->map.line_nbr == info->map.size)
	{
		if (info->map.line_nbr == info->map.size)
			info->map.size *= 2;
		new_map = NULL;
		if (!(new_map = malloc(sizeof(char *) * info->map.size)))
			lemin_error("malloc error in save_lines");
		if (NULL != info->map.lines)
		{
			map_counter = -1;
			while (++map_counter < info->map.size / 2)
				new_map[map_counter] = info->map.lines[map_counter];
			ft_memdel((void**)&(info->map.lines));
		}
		info->map.lines = new_map;
	}
	if (duplicate_or_save == SAVE_ADRESS)
		info->map.lines[info->map.line_nbr] = buf;
	else if (NULL == (info->map.lines[info->map.line_nbr] = ft_strdup(buf)))
		lemin_error("ft_strdup error in save_lines");
	info->map.line_nbr++;
}

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
		else if (buf)
		{
			save_lines(&info, buf, DUPLICATE);
			info = tube_assign(buf, info);
		}
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
			info = store_node_handler(info, node_create(buf, node_number++));
			info.end_begin_room = 0;
		}
		if (buf)
			save_lines(&info, buf, SAVE_ADRESS);
		ret = get_next_line(0, &buf, '\n');
	}
	lemin_error("no tubes after room declaration or GNL return was < 1");
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
			lemin_error("get_next_line returned -1 in parse_map or void_map");
		if (buf[0] == '#')
			info = comment_mannagement(buf, info);
		if (!info.ant_nb)
		{
			if (!(info.ant_nb = ft_atoi(buf)))
				lemin_error("First line must be ant number > 0");
		}
		else if (info.ant_nb)
		{
			info = get_rooms(info, buf);
			return (info);
		}
		if (buf)
			save_lines(&info, buf, SAVE_ADRESS);
	}
	return (info);
}
