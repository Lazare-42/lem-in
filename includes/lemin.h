/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:48:16 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/11 20:05:18 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define HASH_MULTIPLIER 37
# define END 230982
# define BEGINNING 34303
# define HASH_INITIAL_SIZE 1024
# define GROWTH_FACTOR 2

typedef	struct		s_node t_node;

typedef	struct		s_hash_elem
{
	const char		*name;
	int				number;
	void			*next;
}					t_hash_elem;

typedef	struct		s_hash_table
{
	int				size;
	int				n;
	t_hash_elem		**hash_table;
}					t_hash_table;

typedef	struct		s_node
{
	int				**path_marker;
	int				**matrix_graph;
	int				matrix_size;
}					t_node;

void	lemin_error(char *error);

#endif
