/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:48:16 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/04 21:18:28 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define DATA_MULTIPLIER 37
#define NO_PATH 1231501
# define END -1
# define START 1
# define DATA_INITIAL_SIZE 1024
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

typedef enum    	e_type
{
    				std, 
					loop_full,
					deadend_full,
					uselesspath_full
}               	t_type;

typedef struct		s_map_creator
{
	t_type			type;
	int				node_nb;
	int				links_percent;
	int				is_valide;
}					t_map_creator;

typedef struct		s_path
{
	int				node;
	int				node_from;
	int				weight_number;
}					t_path;

typedef struct		s_info
{
	t_node			*hash_table;
	t_node			*nodelist;
	int				end_begin_room;
	int				ant_nbr;
	int				tab_size;
	int				shortest_path;
	int				n;
}					t_info;

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
t_info				comment_mannagement(char *buf, t_info info);
t_info				parse_map(t_info info);
t_info				tube_assign(char *buf, t_info info);
t_info				swap_end_room(t_info info);
int					hashtable_key(const char *name);
t_node				*hash_delete_elem(t_info info, const char *to_find);
const char			*set_get_end_name(const char *end_name);
t_info				swap_end_begin_room(t_info info, int start_or_end);
const char			*set_get_end_name(const char *name);
t_info				djisktra(t_info info);
const char			*set_get_start_name(const char *name);
int     			**map_creator(t_map_creator map_creator_info, char *path);
void				print_map_visualizer(t_info info, char *path);

#endif
