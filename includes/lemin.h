/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:48:16 by lazrossi          #+#    #+#             */
/*   Updated: 2018/10/01 02:06:57 by lazrossi         ###   ########.fr       */
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
# define BIG 100000

typedef	struct		s_node t_node;

typedef	struct		s_node
{
	const char		*name;
	int				number;
	int				x;
	int				y;
	t_node			*next;
}					t_node;

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
	int				**o_mat;
	int				**tmp_mat;
	int				**working_mat;
	int				end_begin_room;
	float			ant_nb;
	int				tab_size;
	int				shortest_path;
	int				n;
	const char		*end_name;
	const char		*begin_name;
}					t_info;

typedef struct	s_ilst
{
	int				n;
	int				ant_index;
	struct s_ilst	*next;
}				t_ilst;

typedef struct	s_plst
{
	int				path_len;
	int				nbf;
	int				nbftot;
	struct s_ilst	*path;
	struct s_ilst	*first_node;
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

typedef struct	s_conflict
{
	int			node_1;
	int			node_2;
	int			distance_from_a;
}				t_conflict;

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
void	get_best_paths(t_info *info, t_best_paths *best_paths, int it_nb);
int		dijkstra(int **mat, int size);
void	plstadd(t_plst **plst, t_plst *new_plst);
void	ilstadd(t_ilst **ilst, t_ilst *new_ilst);
void	plst_print(t_plst **plst);
int		plst_get_len(t_plst **plst);
int		**mat_init(int size);
void	mat_cpy(int **dst_mat, int **src_mat, int size);
void	mat_reset(int **mat, int size);
int		mat_del_joint_path(int **tmp_mat, int **working_mat, int size);
void	mat_del_link(int **tmp_mat, int prev_node_index, int next_node_index);
void	working_mat_add_new_paths(int **working_mat, int **tmp_mat, int n);
void	mat_reverse_used_paths(int **tmp_mat, int **working_mat, int size);
void	ilstdel(t_ilst **ilst);
void	plstdel(t_plst **plst);
void	l_heap_print(int **heap);
int		**l_heap_create(int n);
void	l_heap_add(int **heap, int *node);
int		*l_heap_pick_first(int **heap);
void	l_heap_del(int ***heap);
void	mat_del_node(int **tmp_mat, int **working_mat, int n, int node);
t_ilst	*ilstrev(t_ilst **ilst);
void	output_print(t_best_paths *best_paths, t_info *info);
void	mat_free(int	***mat, int size);
//void	mat_print(int **mat, int size);

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
t_info				comment_mannagement(char *buf, t_info info);
t_info				parse_map(t_info info);
t_info				tube_assign(char *buf, t_info info);
t_info				swap_end_room(t_info info);
int					hashtable_key(const char *name);
t_node				*hash_delete_elem(t_info info, const char *to_find);
void				print_hash_map(t_info info);
t_info				swap_end_begin_room(t_info info, int start_or_end);

#endif
