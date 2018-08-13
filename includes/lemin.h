/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:48:16 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/13 00:52:53 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define DATA_MULTIPLIER 37
# define END 230982
# define BEGINNING 34303
# define DATA_INITIAL_SIZE 1024
# define GROWTH_FACTOR 2

typedef	struct		s_node t_node;

typedef	struct		s_node
{
	const char		*name;
	int				number;
	int				x;
	int				y;
	int				**path_marker;
	void			*next;
}					t_node;

typedef	struct		s_hash_table
{
	int				n;
	t_node			*hash_table;
}					t_hash_table;

typedef struct		s_info
{
	t_node			*hash_table;
	t_node			*nodelist;
	int				size;
	int				n;
}					t_info;

void				lemin_error(char *error);
t_node				*hash_insert(t_info info, t_node new_node);
t_node				hash_retrieve(t_node *table, const char *name, int size);
t_node				*create_resize_hashtable(t_info info);
t_info				store_node_handler(t_info info, t_node new_node);
t_node				node_create(char *buf, int node_number);
t_node				*resize_hashtable(t_info info);
t_node				*create_hashtable(t_info info);
t_node				*resize_nodelist(t_info info);
t_node				*create_nodelist(t_info info);

#endif
