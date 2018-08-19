/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:48:16 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/13 19:01:01 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define DATA_MULTIPLIER 37
# define END -1
# define START 1
# define BEGINNING 34303
# define DATA_INITIAL_SIZE 2
# define GROWTH_FACTOR 2

typedef	struct		s_node t_node;

typedef	struct		s_node
{
	const char		*name;
	int				number;
	int				x;
	int				y;
	int				*tubes;
	int				*weight;
	int				***path_marker;
	t_node			*next;
}					t_node;

typedef struct		s_info
{
	t_node			*hash_table;
	t_node			*nodelist;
	int				end_begin_room;
	int				ant_nbr;
	int				size;
	int				n;
}					t_info;

void				print_map(t_info info, int where);
void				lemin_error(char *error);
t_node				*hash_insert(t_info info, t_node new_node);
t_node				hash_retrieve(t_info info, const char *to_find);
t_node				*create_resize_hashtable(t_info info);
t_info				store_node_handler(t_info info, t_node new_node);
t_node				node_create(char *buf, int node_number);
t_node				*resize_hashtable(t_info info);
t_node				*create_table(t_info info);
t_node				*resize_nodelist(t_info info);
t_info				create_tubes(t_info info);
void				comment_mannagement(char *buf);
t_info				parse_map(t_info info);
t_info				tube_assign(char *buf, t_info info);
t_info				swap_end_room(t_info info);
int					hashtable_key(const char *name);
t_node				*hash_delete_elem(t_info info, const char *to_find);
const char			*set_get_end_name(const char *end_name);
void				print_hash_map(t_info info);
t_info				swap_end_begin_room(t_info info, int start_or_end);
const char			*set_get_end_name(const char *name);
const char			*set_get_start_name(const char *name);

#endif
