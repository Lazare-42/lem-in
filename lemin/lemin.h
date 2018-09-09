/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 16:49:20 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/09 21:20:39 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct  s_info
{
	int         n;
	int         **o_mat;
	int			**tmp_mat;
	int			**working_mat;
	float		ant_nb;
}               t_info;

typedef struct	s_ilst
{
	int				n;
	struct s_ilst	*next;
}				t_ilst;

typedef struct	s_plst
{
	int				path_len;
	struct s_ilst	*path;
	struct s_plst	*next;
}				t_plst;

typedef struct	s_best_paths
{
	struct s_plst	*plst;
	float			time;
}				t_best_paths;

typedef struct	s_node_mem
{
	int			prev_node_i;
	int			next_node_i;
}				t_node_mem;

typedef struct	s_lst_g
{
	t_plst		*new_plst;
	t_plst		*tmp_plst;
	t_ilst		*new_ilst;
	t_ilst		*tmp_ilst;
}				t_lst_g;

typedef struct	s_paths_info
{
	int			paths_total_len;
	int			paths_nb;
	float		time;
}				t_paths_info;

typedef struct	s_node
{
	int			index;
	int			weight;
}				t_node;

int		**queue_create(int n);
void	queue_add_elem(int **queue, int *node);
int		*queue_pick_last(int **queue);
void	queue_print(int **queue, int n);
void    graph_loop_remove(int **mat, int n);
int     graph_link_counter(int **mat, int n);
void    graph_dead_end_remove(int **mat, int n);
void    graph_useless_node_remove(int **mat, int n);
void    mat_init_for_dijkstra(int **mat, int n);
void    graph_orientation(int **mat, int n);
void	ilst_print(t_ilst **ilst);
t_ilst	*ilstnew(int const n);
t_plst	*plstnew(t_ilst *path);
void	mat_print(int **mat, int size);
t_best_paths	get_best_paths(t_info *info, int it_nb);
int		dijkstra(int **mat, int size);
void	plstadd(t_plst **plst, t_plst *new_plst);
void	ilstadd(t_ilst **ilst, t_ilst *new_ilst);
void	plst_print(t_plst **plst);
int		plst_get_len(t_plst **plst);
int		**mat_init(int size);
void	mat_cpy(int **dst_mat, int **src_mat, int size);
void	mat_reset(int **mat, int size);
void	mat_del_joint_path(int **tmp_mat, int **working_mat, int size);
void	mat_del_link(int **tmp_mat, int prev_node_index, int next_node_index);
void	working_mat_add_new_paths(int **working_mat, int **tmp_mat, int n);
void	mat_reverse_used_paths(int **tmp_mat, int **working_mat, int size);
void	ilstdel(t_ilst **ilst);
void	plstdel(t_plst **plst);
void	heap_print(t_node *heap);
t_node	*heap_create(int n);
void	heap_add(t_node *heap, t_node node);
t_node	heap_pick_first(t_node *heap);
void	l_heap_print(int **heap);
int		**l_heap_create(int n);
void	l_heap_add(int **heap, int *node);
int		*l_heap_pick_first(int **heap);
void	l_heap_del(int ***heap);

#endif
