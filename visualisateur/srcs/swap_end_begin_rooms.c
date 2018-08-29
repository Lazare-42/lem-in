/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_end_begin_rooms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:47 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/20 15:05:48 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include <stdlib.h>

static t_info	swap_nodelist_endroom(t_info info, int start_or_end)
{
	t_node	end_begin;
	t_node	swap;

	if (start_or_end == END)
	{
		end_begin = hash_retrieve(info, set_get_end_name(NULL));
		swap = info.nodelist[info.n - 1];
		info.nodelist[info.n - 1] = end_begin;
		info.nodelist[end_begin.number] = swap;
	}
	else if (start_or_end == START)
	{
		end_begin = hash_retrieve(info, set_get_start_name(NULL));
		swap = info.nodelist[0];
		info.nodelist[0] = end_begin;
		info.nodelist[end_begin.number] = swap;
	}
	return (info);
}

t_info	swap_end_begin_room(t_info info, int start_or_end)
{
	t_node		end_begin;
	t_node		swap;
	const char	*name;
	int			tmp_nbr;
	int			where;

	where = (start_or_end == START) ? 0 : info.n - 1;
	name = (start_or_end == START) ?
		set_get_start_name(NULL) : set_get_end_name(NULL);
	swap = info.nodelist[where];
	info = swap_nodelist_endroom(info, start_or_end);
	end_begin = hash_retrieve(info, name);
	if (swap.name != end_begin.name)
	{
		info.hash_table = hash_delete_elem(info, end_begin.name);
		info.hash_table = hash_delete_elem(info, swap.name);
		tmp_nbr = swap.number;
		swap.number = end_begin.number;
		end_begin.number = tmp_nbr;
		info.hash_table = hash_insert(info, end_begin);
		info.hash_table = hash_insert(info, swap);
	}
	if (start_or_end == START)
		return (swap_end_begin_room(info, END));
	return (info);
}
