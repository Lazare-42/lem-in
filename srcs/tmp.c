/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure_operations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:17 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/28 15:50:26 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

static void		old_hashtable_memdel(t_info info, t_node **old_hashtable)
{
	int		i;
	t_node	*tmp;
	t_node	*to_del;

	i = -1;
	while (++i < info.tab_size / 2)
	{
		tmp = (*old_hashtable)[i].next;
		while (tmp)
		{
			to_del = tmp;
			tmp = tmp->next;
			ft_memdel((void**)&to_del);
		}
	}
	ft_memdel((void**)old_hashtable);
}

static t_node	*collisioned_node_reinsertion(t_node *collisioned_node,
		t_node *new_hashtable, t_info info)
{
	t_node	*tmp;

	while (collisioned_node)
	{
		tmp = collisioned_node->next;
		collisioned_node->next = NULL;
		new_hashtable = hash_insert(info, *collisioned_node);
		ft_memdel((void**)&collisioned_node);
		collisioned_node = tmp;
	}
	return (new_hashtable);
}

t_node			*resize_hashtable(t_info info)
{
	int		i;
	t_node	*collisioned_node;
	t_node	*new_hashtable;
	t_node	*old_hashtable;

	i = -1;
	old_hashtable = info.hash_table;
	new_hashtable = create_table(info);
	info.hash_table = new_hashtable;
	while (++i < info.tab_size / 2)
	{
		if (old_hashtable[i].name)
		{
			collisioned_node = old_hashtable[i].next;
			old_hashtable[i].next = NULL;
			new_hashtable = hash_insert(info, old_hashtable[i]);
			if (collisioned_node)
				collisioned_node_reinsertion(
				collisioned_node, new_hashtable, info);
		}
	}
	old_hashtable_memdel(info, &old_hashtable);
	return (new_hashtable);
}

t_node			*resize_nodelist(t_info info)
{
	t_node	*new_nodelist;
	int		i;
	t_node	void_node;

	i = -1;
	void_node.name = NULL;
	new_nodelist = create_table(info);
	while (++i < info.tab_size / 2)
		new_nodelist[i] = info.nodelist[i];
	while (++i < info.tab_size)
		new_nodelist[i] = void_node;
	ft_memdel((void**)&info.nodelist);
	return (new_nodelist);
}

t_node			*create_table(t_info info)
{
	t_node	*new_nodelist;
	t_node	void_node;
	int		i;

	new_nodelist = NULL;
	void_node.name = NULL;
	void_node.next = NULL;
	if (!(new_nodelist = malloc(sizeof(t_node) * info.tab_size)))
		lemin_error("malloc error in retab_size_nodelist");
	i = -1;
	while (++i < info.tab_size)
		new_nodelist[i] = void_node;
	return (new_nodelist);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:56:02 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/30 22:02:29 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <limits.h>

static void	mat_reset_for_dijkstra(int **mat, int size)
{
	int y;

	mat[1][0] = 0;
	y = 2;
	while (y < size)
	{
		mat[y][0] = INT_MAX;
		y++;
	}
}

int			dijkstra(int **mat, int size)
{
	int	*node;
	int	**heap;
	int	x;
	int	weight;

	node = &(mat[1][0]);
	heap = l_heap_create(size);
	l_heap_add(heap, node);
	mat_reset_for_dijkstra(mat, size);
	while ((node = l_heap_pick_first(heap)))
	{
		x = 0;
		weight = *node;
		while (++x < size)
		{
			if (node[x] && weight + node[x] < mat[x][0] && weight + node[x] > 0)
			{
				mat[x][0] = weight + node[x];
				l_heap_add(heap, &(mat[x][0]));
				if (x == size - 1)
					return (1);
			}
		}
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 14:03:10 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/25 20:30:07 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <unistd.h>
#include <fcntl.h>

void	lemin_error(char *error)
{
	int fd;

	fd = open("/Users/lazrossi/Documents/42/lem-in/error_trace.txt",
			O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	ft_dprintf(fd, "%s\n", error);
	close(fd);
	ft_myexit("ERROR");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:59:12 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/18 14:35:15 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	mat_print(int **mat, int size)
{
	int y;
	int x;

	y = 0;
	x = 0;
	printf(" X  N ");
	while (++x < size)
		printf("%2c ", x + 64); fflush(stdout);
	printf("\n N "); fflush(stdout);
	while (y < size)
	{
		x = -1;
		if (y)
			printf("%2c ", y + 64); fflush(stdout);
		while (++x < size)
		{
			if (x == 0 || y == 0) {
				printf("\033[33m%2d \033[0m", mat[y][x]); fflush(stdout);
			}
			else if (x == y) {
				printf("\033[32m%2d \033[0m", mat[y][x]); fflush(stdout);
			}
			else if (mat[y][x] == 0) {
				printf("\033[31m 0 \033[0m"); fflush(stdout);
			}
			else {
				printf("\033[34m%2d \033[0m", mat[y][x]); fflush(stdout);
			}
		}
		printf("\n"); fflush(stdout);
		y++;
	}
}

void	mat_free(int	***mat, int size)
{
	int y;

	y = 0;
	while (y < size)
	{
		free((*mat)[y]);
		y++;
	}
	free(*mat);
}

int		**mat_init(int size)
{
	int **mat;
	int y;
	int x;

	y = 0;
	mat = (int **)malloc(sizeof(int *) * size);
	while (y < size)
	{
		x = 0;
		mat[y] = (int *)malloc(sizeof(int) * size);
		while (x < size)
		{
			mat[y][x] = 0;
			x++;
		}
		y++;
	}
	return (mat);
}

void	mat_cpy(int **dst_mat, int **src_mat, int size)
{
	int y;
	int x;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			dst_mat[y][x] = src_mat[y][x];
			x++;
		}
		y++;
	}
}

void	mat_reset(int **mat, int size)
{
	int y;
	int x;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mat[y][x] = 0;
			x++;
		}
		y++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:00:14 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/30 23:26:07 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <limits.h>

int				get_paths_total_len(t_plst **plst)
{
	t_plst	*tmp;
	int		len;

	tmp = *plst;
	len = 0;
	while (tmp)
	{
		len += tmp->path_len;
		tmp = tmp->next;
	}
	return (len);
}

int				get_next(int **mat, int size, int current_index)
{
	int	x;
	int	lighter_weight;
	int	lighter_node_index;
	int	weight;

	x = 1;
	lighter_weight = 99;
	lighter_node_index = size - 2;
	if (current_index == 0)
		return (-1);
	while (x < size)
	{
		if (mat[current_index + 1][x] > 0 && (weight = mat[x][0])
			< lighter_weight)
		{
			lighter_weight = weight;
			lighter_node_index = x;
		}
		x++;
	}
	return (lighter_node_index - 1);
}

void			update_best_paths(t_best_paths *best_paths, t_plst *new_plst, /*int ant_nb*/ float new_time)
{
	if (new_time < best_paths->time)
	{
		if (best_paths->time != INT_MAX)
			plstdel(&(best_paths->plst));
		best_paths->plst = new_plst;
		best_paths->time = new_time;
	}
	else
	{
		plstdel(&new_plst);
	}
}

int				add_path_if_usefull(float ant_nb, t_paths_info *p_info, t_lst_g *lst_g)
{
	float	new_time;
	int		better_path_found;

	better_path_found = 0;
	new_time = (ant_nb + p_info->paths_total_len - p_info->paths_nb) / p_info->paths_nb;
	if (new_time <  p_info->time)
	{
		p_info->time = new_time;
		lst_g->tmp_plst->path = lst_g->new_ilst;
		plstadd(&(lst_g->new_plst), lst_g->tmp_plst);
		better_path_found = 1;
	}
	else
		ilstdel(&(lst_g->new_ilst));
	return (better_path_found);
}

void			p_info_init(t_paths_info *p_info)
{
	p_info->paths_total_len = 0;
	p_info->paths_nb = 0;
	p_info->time = INT_MAX;
}

void			mat_del_links(int **tmp_mat, int **working_mat, int node_from, int node_to)
{
	tmp_mat[node_from][node_to] = 0;
	tmp_mat[node_to][node_from] = 0;
	working_mat[node_from][node_to] = -1;
	working_mat[node_to][node_from] = -1;
}

void			mat_del_node(int **tmp_mat, int **working_mat, int n, int node)
{
	int	y;

	if (node + 2 == n)
	{
		printf("plop\n"); fflush(stdout);
		return;
	}
	y = 1;
	while (y < n)
	{
		if (tmp_mat[y][node + 1])
		{
			tmp_mat[y][node + 1] = 0;
			working_mat[y][node + 1] = -1;
		}
		y++;
	}
}

void			save_paths_from_mat_if_better(t_info *info,
	t_best_paths *best_paths)
{
	t_lst_g			lst_g;
	t_node_mem		n_mem;
	t_paths_info	p_info;

	lst_g.new_plst = plstnew(0);
	p_info_init(&p_info);
	while (dijkstra(info->tmp_mat, info->n + 1))
	{
		n_mem.prev_node_i = info->n - 1;
		lst_g.new_ilst = ilstnew(info->n - 1);
		lst_g.tmp_plst = plstnew(lst_g.new_ilst);
		p_info.paths_nb++;
		while ((n_mem.next_node_i = get_next(info->tmp_mat, info->n + 1,
			lst_g.new_ilst->n)) >= 0 && ++(lst_g.tmp_plst->path_len) && ++p_info.paths_total_len)
		{
			if (n_mem.prev_node_i + 1 != info->n)
				mat_del_node(info->tmp_mat, info->working_mat, info->n + 1, n_mem.prev_node_i);
			else
				mat_del_links(info->tmp_mat, info->working_mat, n_mem.prev_node_i + 1, n_mem.next_node_i + 1);
			info->working_mat[n_mem.next_node_i + 1][n_mem.prev_node_i + 1] = info->tmp_mat[n_mem.prev_node_i + 1][0];
			info->working_mat[0][n_mem.prev_node_i + 1] += 1;
			n_mem.prev_node_i = n_mem.next_node_i;
			lst_g.tmp_ilst = ilstnew(n_mem.next_node_i);
			ilstadd(&(lst_g.new_ilst), lst_g.tmp_ilst);
			//ilstdel(&(lst_g.tmp_ilst));
		}
		//printf("plstdel\n"); fflush(stdout);
		//plstdel(&(lst_g.tmp_plst));
		if (!(add_path_if_usefull(info->ant_nb, &p_info, &lst_g)))
			break;
	}
	update_best_paths(best_paths, lst_g.new_plst, p_info.time);
}

void	mat_del_last_conflict(int **tmp_mat, int **working_mat, int n)
{
	t_conflict	conflict;
	int			y;
	int			x;
	int			is_conflict;

	conflict.node_1 = 0;
	conflict.node_2 = 0;
	conflict.distance_from_a = 0;
	is_conflict = 0;
	x = 1;
	while (x < n - 1)
	{
		if (working_mat[0][x] >= 2)
		{
			y = 1;
			is_conflict = 1;
			while (y < n - 1)
			{
				if (working_mat[y][x] > conflict.distance_from_a && working_mat[y][x] != BIG)
				{
					conflict.distance_from_a = working_mat[y][x];
					conflict.node_1 = y;
					conflict.node_2 = x;
				}
				y++;
			}
		}
		x++;
	}
	tmp_mat[conflict.node_1][conflict.node_2] = 0;
	tmp_mat[conflict.node_2][conflict.node_1] = 0;
}

void			mat_put_reversed_path(int **tmp_mat, int**working_mat, int n)
{
	int	y;
	int	x;

	y = 1;
	while (y < n)
	{
		x = 1;
		while (x < n)
		{
			if (working_mat[y][x] != 0)
			{
				tmp_mat[y][x] = 1;
				tmp_mat[x][y] = 1;
			}
			x++;
		}
		y++;
	}
}

t_best_paths	get_best_paths(t_info *info, int it_nb)
{
	int				i;
	t_best_paths	best_paths;

	info->tmp_mat = mat_init(info->n + 1);
	info->working_mat = mat_init(info->n + 1);
	best_paths.time = INT_MAX;
	best_paths.plst = plstnew(0);
	i = 0;
	mat_cpy(info->tmp_mat, info->o_mat, info->n + 1);
	while (i < it_nb)
	{
		mat_put_reversed_path(info->tmp_mat, info->working_mat, info->n + 1);
		if (!(mat_del_joint_path(info->tmp_mat, info->working_mat, info->n)))
			mat_del_last_conflict(info->tmp_mat, info->working_mat, info->n);
		mat_reset(info->working_mat, info->n);
		save_paths_from_mat_if_better(info, &best_paths);
		mat_put_reversed_path(info->tmp_mat, info->working_mat, info->n + 1);
		mat_reverse_used_paths(info->tmp_mat, info->working_mat, info->n + 1);
		working_mat_add_new_paths(info->working_mat, info->tmp_mat, info->n);
		i++;
	}
	return (best_paths);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 15:54:19 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/28 15:46:58 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

int				hashtable_key(const char *name)
{
	unsigned const char *string;
	int					pos;

	if (!name)
		return (0);
	pos = 0;
	string = (unsigned const char *)name;
	while (*string)
	{
		pos = (DATA_MULTIPLIER * pos) + *string;
		string++;
	}
	if (pos < 0)
		pos *= -1;
	return (pos);
}

t_node			*hash_insert(t_info info, t_node new_node)
{
	int		key;
	t_node	*tmp;
	t_node	*new;

	new_node.next = NULL;
	key = hashtable_key(new_node.name) % info.tab_size;
	if (info.hash_table[key].name
			&& ft_strcmp(new_node.name, info.hash_table[key].name))
	{
		tmp = &info.hash_table[key];
		while (tmp->next)
			tmp = tmp->next;
		if (!(new = malloc(sizeof(t_node))))
			lemin_error("malloc error in hash_insert");
		*new = new_node;
		tmp->next = new;
	}
	else
		info.hash_table[key] = new_node;
	return (info.hash_table);
}

t_node			hash_retrieve(t_info info, const char *to_find)
{
	int		hash_key;
	t_node	tmp;

	hash_key = hashtable_key(to_find) % info.tab_size;
	tmp = info.hash_table[hash_key];
	if (!tmp.name)
		lemin_error("incoreect room name passed in tubes");
	if (to_find[0] != tmp.name[0] && ft_strcmp(to_find, tmp.name))
	{
		while (ft_strcmp(to_find, tmp.name))
			tmp = *tmp.next;
	}
	if (!tmp.name)
		lemin_error("incorrect room name passed in tubes");
	return (tmp);
}

static t_node	*list_search_to_del(t_info info, const char *to_find,
		int hash_key)
{
	t_node	*tmp;
	t_node	*malloced_node;

	tmp = NULL;
	malloced_node = info.hash_table[hash_key].next;
	if (!ft_strcmp(malloced_node->name, to_find))
		info.hash_table[hash_key].next = NULL;
	else
	{
		while (ft_strcmp(malloced_node->name, to_find))
		{
			tmp = malloced_node;
			malloced_node = malloced_node->next;
		}
	}
	if (tmp)
		tmp->next = malloced_node->next;
	ft_memdel((void**)&malloced_node);
	return (info.hash_table);
}

t_node			*hash_delete_elem(t_info info, const char *to_find)
{
	int		hash_key;
	t_node	simple_node;
	t_node	*tmp;

	hash_key = hashtable_key(to_find) % info.tab_size;
	simple_node = info.hash_table[hash_key];
	tmp = NULL;
	if (ft_strcmp(to_find, info.hash_table[hash_key].name))
		info.hash_table = list_search_to_del(info, to_find, hash_key);
	else
	{
		if (info.hash_table[hash_key].next)
		{
			tmp = info.hash_table[hash_key].next;
			info.hash_table[hash_key] = *tmp;
			ft_memdel((void**)&tmp);
		}
		else
			info.hash_table[hash_key].name = NULL;
	}
	return (info.hash_table);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 22:34:22 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/30 21:52:13 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	l_heap_del(int ***heap)
{
	free((*heap)[0]);
	free(*heap);
}

void	l_heap_print(int **heap)
{
	int	i;

	i = 1;
	ft_printf("\033[31mHEAP - len %d\n\033[0m", heap[0][0]);
	while (i < heap[0][0] + 1)
	{
		ft_printf(" %03d | node add : %03x | node weight : %03d\n", i,
			(int)heap[i], heap[i][0]);
		i++;
	}
}

int		**l_heap_create(int n)
{
	static int	**heap = 0;
	int			i;
	int			*first;

	first = NULL;
	if (heap == 0)
	{
		if (!(first = (int*)malloc(sizeof(int) * 1)))
			ft_myexit("l_heap_create : malloc error");
		if (!(heap = (int **)malloc(sizeof(int *) * (n + 1))))
			ft_myexit("l_heap_create : malloc error");
		heap[0] = first;
		heap[0][0] = 0;
	i = 1;
		while (i < n + 1)
		{
			heap[i] = 0;
			i++;
		}
	}
	return (heap);
}

int		l_heap_chrnul(int **heap, int *node)
{
	int		size;
	int		i;

	size = heap[0][0];
	i = 0;
	while (++i < size)
	{
		if (heap[i] == node)
			break;
	}
	return (i);
}

void	l_heap_add(int **heap, int *node)
{
	int		i;
	int		*tmp;


	heap[0][0]++;

	if ((i = l_heap_chrnul(heap, node)) != heap[0][0])
		heap[0][0]--;
	heap[i] = node;
	while (i > 1 && heap[i][0] < heap[i / 2][0])
	{
		tmp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = tmp;
		i /= 2;
	}
}

int		*l_heap_pick_first(int **heap)
{
	int		i;
	int		*tmp;
	int		*ret;

	i = 1;
	if (!heap[0][0])
		return (0);
	ret = heap[1];
	heap[1] = heap[heap[0][0]--];
	while ((i * 2 < heap[0][0] && heap[i][0] > heap[i * 2][0]) || (i * 2 + 1 < heap[0][0] && heap[i][0]
		> heap[i * 2 + 1][0]))
	{
		tmp = heap[i];
		if (heap[2 * i][0] < heap[2 * i + 1][0])
		{
			heap[i] = heap[2 * i];
			heap[2 * i] = tmp;
			i = 2 * i;
		}
		else if (i * 2 + 1 < heap[0][0])
		{
			heap[i] = heap[2 * i + 1];
			heap[2 * i + 1] = tmp;
			i = 2 * i + 1;
		}
		else
			break;
	}
	return (ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_ilst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:18:15 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/30 23:26:23 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_ilst	*ilstnew(int const n)
{
	t_ilst	*new_m;

	new_m = 0;
	if (!(new_m = (t_ilst*)malloc(sizeof(t_ilst))))
		return (0);
	new_m->n = n;
	new_m->ant_index = 0;
	new_m->next = NULL;
	return (new_m);
}

void	ilstadd(t_ilst **ilst, t_ilst *new_ilst)
{
	new_ilst->next = *ilst;
	*ilst = new_ilst;
}

t_ilst	*ilstrev(t_ilst **head)
{
	t_ilst	*prev;
	t_ilst	*next;
	t_ilst	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}

void	ilstdel(t_ilst **ilst)
{
	t_ilst	*tmp;

//	printf("ilstdel enter\n"); fflush(stdout);
	if (!(ilst) || ilst == (t_ilst **)16)
		return;
//	printf("ilstdel after check 0 - ilst = %ld\n", (long)ilst); fflush(stdout);
	tmp = *ilst;
//	printf("ilstdel after tmp initialized - tmp = %ld\n", (long)tmp); fflush(stdout);
	while (*ilst && *ilst != (t_ilst *)12)
	{
//		printf("ilstdel loop\n"); fflush(stdout);
		*ilst = tmp->next;
		free(tmp);
		tmp = *ilst;
	}
}

void	ilst_print(t_ilst **ilst)
{
	t_ilst	*tmp;
	int		i;

	tmp = *ilst;
	i = 0;
	while (tmp)
	{
		ft_printf("node %d: %c\n", i, tmp->n + 65);
		tmp = tmp->next;
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:41 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/30 23:28:02 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

static	int		w_get_next(int **tmp_mat, int **working_mat, int size, int	current_index)
{
	int	x;
	int	lighter_weight;
	int	lighter_node_index;
	int	weight;

	(void)working_mat;

	x = 1;
	lighter_weight = 99;
	lighter_node_index = size - 2;
	if (current_index == 0)
		return (-1);
	while (x < size)
	{
		if ((tmp_mat[current_index + 1][x] > 0 || tmp_mat[x][current_index + 1] == -1) && (weight = tmp_mat[x][0]) < lighter_weight)
		{
			lighter_weight = weight;
			lighter_node_index = x;
		}
		x++;
	}
	return (lighter_node_index - 1);
}

int		mat_del_joint_path(int **tmp_mat, int **working_mat, int size)
{
	int y;
	int x;
	int	path_deleted;

	path_deleted = 0;
	y = 1;
	while (y < size)
	{
		x = y;
		while (x < size)
		{
			if (working_mat[y][x] > 0 && working_mat[x][y] > 0)
			{
				path_deleted = 1;
				tmp_mat[y][x] = 0;
				tmp_mat[x][y] = 0;
			}
			x++;
		}
		y++;
	}
	return (path_deleted);
}

void	mat_del_link(int **tmp_mat, int prev_node_index, int next_node_index)
{
	tmp_mat[prev_node_index + 1][next_node_index + 1] = 0;
	tmp_mat[next_node_index + 1][prev_node_index + 1] = 0;
}

void	working_mat_add_new_paths(int **working_mat, int **tmp_mat, int n)
{
	int		next_node_index;
	int		prev_node_index;

	while (dijkstra(tmp_mat, n + 1))
	{
		prev_node_index = n - 1;
		while ((next_node_index = w_get_next(tmp_mat, working_mat, n + 1, prev_node_index)) >= 0)
		{
			mat_del_node(tmp_mat, working_mat, n, prev_node_index);
			working_mat[next_node_index + 1][prev_node_index + 1] = BIG;
			working_mat[0][prev_node_index + 1] += 1;
			prev_node_index = next_node_index;
		}
	}
}

void	mat_reverse_used_paths(int **tmp_mat, int **working_mat, int size)
{
	int y;
	int x;

	y = 1;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (working_mat[y][x] > 0)
			{
				tmp_mat[y][x] = 0;
				tmp_mat[x][y] = -1;
			}
			x++;
		}
		y++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_plst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:44:40 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/18 15:28:04 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_plst	*plstnew(t_ilst *path)
{
	t_plst	*new_m;

	new_m = 0;
	if (!(new_m = (t_plst*)malloc(sizeof(t_plst))))
		return (0);
	new_m->path = path;
	new_m->path_len = 0;
	new_m->nbftot = 0;
	new_m->nbf = 0;
	new_m->first_node = 0;
	new_m->next = NULL;
	return (new_m);
}

void	plstadd(t_plst **plst, t_plst *new_plst)
{
	new_plst->next = *plst;
	*plst = new_plst;
}

void	plstdel(t_plst **plst)
{
	t_plst	*tmp;

	if (!(plst))
		return;
	tmp = *plst;
	while (*plst)
	{
		*plst = tmp->next;
		ilstdel(&((*plst)->path));
		free(tmp);
		tmp = *plst;
	}
}

int		plst_get_len(t_plst **plst)
{
	t_plst	*tmp;
	int		len;

	tmp = *plst;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

void	plst_print(t_plst **plst)
{
	t_plst	*tmp;
	int		i;

	tmp = *plst;
	i = 0;
	while (tmp)
	{
		ft_printf("\nCHEMIN %d - LEN %d - NBFTOT %d\n\n", i, tmp->path_len, tmp->nbftot);
		ilst_print(&(tmp->path));
		tmp = tmp->next;
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/30 22:30:53 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <math.h>
//unistd is for sleep / chechking leaks ; take it away when done

t_info	comment_mannagement(char *buf, t_info info)
{
	if (ft_memcmp(buf, "##end", 5) && ft_memcmp(buf, "##start", 7))
	{
		(void)buf;
	// Attention : you need to strdup buf if you want to use the commentary
	}
	if (ft_strequ(buf, "##end"))
		info.end_begin_room = END;
	else if (ft_strequ(buf, "##start"))
		info.end_begin_room = START;
	return (info);
}
#include <unistd.h>
int		main()
{
	t_info	info;
	t_best_paths	best_paths;

	info.n = 0;
	info.end_begin_room = 0;
	info.tab_size = DATA_INITIAL_SIZE;
	info.ant_nb = 0;
	info.hash_table = create_table(info);
	info.nodelist = create_table(info);
	info = parse_map(info);
	best_paths = get_best_paths(&info, 10);
	//printf("\nBEST SET OF PATHS : %.1f time\n", best_paths.time); plst_print(&(best_paths.plst));
	//print_map(info, 2);
	output_print(&best_paths, &info);
	/* !! */
//	print_hash_map(info);
//	print_map(info, 0);
//	sleep(130);
	/* !! */
	mat_free(&(info.working_mat), info.n + 1);
	mat_free(&(info.tmp_mat), info.n + 1);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:06:37 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/06 01:49:46 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_from_model(int y, int x)
{
	static int  model[11][11] =
	{//  X  A  B  C  D  E  F  G  H  I  J
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //X
		{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1}, //A
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //B
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //C
		{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //D
		{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}, //E
		{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0}, //F
		{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0}, //G
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}, //H
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, //I
		{0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0}, //J
	};
	return (model[y][x]);
}

int		**mat_init_from_model(int n)
{
	int **mat;
	int y;
	int x;

	y = 0;
	mat = (int **)malloc(sizeof(int *) * (n + 1));
	while (y < n + 1)
	{
		x = 0;
		mat[y] = (int *)malloc(sizeof(int) * (n + 1));
		while (x < n + 1)
		{
			mat[y][x] = get_from_model(y, x);
			x++;
		}
		y++;
	}
	return (mat);
}

void	mat_print(int **mat, int size)
{
	int y;
	int x;

	y = 0;
	x = 0;
	printf(" X  N ");
	while (++x < size)
		printf("%2c ", x + 64);
	printf("\n N ");
	while (y < size)
	{
		x = -1;
		if (y)
			printf("%2c ", y + 64);
		while (++x < size)
		{
			if (x == 0 || y == 0)
				printf("\033[33m%2d \033[0m", mat[y][x]);
			else if (x == y)
				printf("\033[32m%2d \033[0m", mat[y][x]);
			else if (mat[y][x] == 0)
				printf("\033[31m 0 \033[0m");
			else
				printf("\033[34m%2d \033[0m", mat[y][x]);
		}
		printf("\n");
		y++;
	}
}

int	main(void)
{
	int				**mat;
	t_info			*info;
	t_best_paths	best_paths;

	info = (t_info *)malloc(sizeof(t_info));
	info->n = 10;
	info->ant_nb = 10;
	info->o_mat = mat_init_from_model(info->n);
	printf("O MAT\n"); mat_print(info->o_mat, info->n + 1);
	best_paths = get_best_paths(info, 2);
	printf("\nBEST SET OF PATHS : %.1f time\n", best_paths.time); plst_print(&(best_paths.plst));
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 03:58:24 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/29 20:26:44 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <math.h>

static void	nbfpp_add(t_best_paths *best_paths, int ant_nb)
{
	t_plst	*plst;
	int		time;
	int		nbftot;

	plst = best_paths->plst;
	time = ceil(best_paths->time);
	while (plst)
	{
		nbftot = time - plst->path_len + 1;
		if (ant_nb > nbftot)
		{
			plst->nbftot = nbftot;
			ant_nb -= nbftot;
		}
		else
		{
			plst->nbftot = ant_nb;
			ant_nb = 0;
		}
		plst = plst->next;
	}
}

static void	path_reverse(t_best_paths *best_paths)
{
	t_plst	*plst;

	plst = best_paths->plst;
	while (plst)
	{
		plst->first_node = plst->path;
		plst->path = ilstrev(&(plst->path));
		plst = plst->next;
	}
}

static void	ilst_move(t_ilst *ilst, t_info info)
{
	(void)info;
	while (ilst)
	{
		if (ilst->next)
		{
		if (ilst->next->ant_index)
			{
				ilst->ant_index = ilst->next->ant_index;
				ilst->next->ant_index = 0;
				ft_printf("L%d-%s ", ilst->ant_index, info.nodelist[ilst->n].name);
			}
		}
		ilst = ilst->next;
	}
}

static void	move_print(t_best_paths *best_paths, t_info info)
{
	int		time;
	int		time_tot;
	int		new_ant_index;
	t_plst	*plst;

	time = 0;
	time_tot = ceil(best_paths->time);
	new_ant_index = 0;
	while (time < time_tot)
	{
		plst = best_paths->plst;
		while (plst)
		{
			if (plst->nbftot)
			{
				new_ant_index++;
				plst->first_node->ant_index = new_ant_index;
				plst->nbftot--;
			}
			ilst_move(plst->path, info);
			plst = plst->next;
		}
		ft_printf("\n");
		time++;
	}
}

void	output_print(t_best_paths *best_paths, t_info *info)
{
	nbfpp_add(best_paths, info->ant_nb);
	path_reverse(best_paths);
	move_print(best_paths, *info);
}
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
			info = store_node_handler(info, node_create(buf, node_number++));
			info.end_begin_room = 0;
		}
		ft_memdel((void**)&buf);
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
		ft_memdel((void**)&buf);
	}
	return (info);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:39 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/20 15:05:39 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

void	print_rooms(t_info info)
{
	int i;
	i = 0;

	while (info.nodelist[i].name)
	{
		ft_printf("[[~/Documents/42/lem-in/map.txt]]%10s is room name, %d x %d y\n",
				info.nodelist[i].name, info.nodelist[i].x, info.nodelist[i].y);
		i++;
	}
	i = 0;
	t_node *tmp;
	while (i < info.tab_size)
	{
		if (info.hash_table[i].name)
			ft_printf("[[~/Documents/42/lem-in/map_hash.txt]]%10s is room name, %d x %d y\n",
					info.hash_table[i].name, info.hash_table[i].x, info.hash_table[i].y);
		tmp = info.hash_table[i].next;
		while (tmp)
		{
			ft_printf("[[~/Documents/42/lem-in/map_hash.txt]]%10s is room name %d x %d y COLLISION\n", tmp->name, tmp->x, tmp->y);
			tmp = tmp->next;
		}
		i++;
	}
	ft_printf("[[~/Documents/42/lem-in/map_hash.txt]]%d is list tab_size %d is list node numbers\n", info.tab_size, info.n);
	ft_printf("[[~/Documents/42/lem-in/map.txt]]%d is list tab_size %d is list node numbers\n", info.tab_size, info.n);

}

void	print_hash_map(t_info info)
{
	int i;
	int	null_tab_size;
	int	elem_number;
	t_node *tmp;

	i = -1;
	null_tab_size = 0;
	elem_number = 0;
	ft_printf("[[yellow]][[underline]][[bold]]HASHMAP:\n[[end]]");
	while (++i < info.tab_size)
	{
		if (info.hash_table[i].name)
		{
			if (null_tab_size)
				ft_printf("[[magenta]][null] * % -d\n[[end]]", null_tab_size);
			null_tab_size = 0;
			if ((ft_strcmp(info.hash_table[i].name, (set_get_end_name(NULL))) && ft_strcmp(info.hash_table[i].name, set_get_start_name(NULL))))
				ft_printf("[[green]]%s[[end]]", info.hash_table[i].name);
			else
				ft_printf("[[yellow]]%s[[end]]", info.hash_table[i].name);
			ft_printf("[[italic]]°%-6d[[end]]", info.hash_table[i].number);
			tmp = info.hash_table[i].next;
			elem_number++;
			while (tmp)
			{
				elem_number++;
				if ((ft_strcmp(tmp->name, set_get_end_name(NULL))) && ft_strcmp(tmp->name, set_get_start_name(NULL)))
					ft_printf("[[blue]]->   [[end]][[green]]%s", tmp->name);
				else
					ft_printf("[[blue]]->   [[end]][[yellow]]%s", tmp->name);
				ft_printf("[[end]][[italic]]°%-6d[[end]]", tmp->number);
				tmp = tmp->next;
			}
			ft_printf("\n");
		}
		else
			null_tab_size++;
	}
	ft_printf("[[bold]][[underline]]Total elements[[end]] : [[red]][[italic]]%d\n[[end]]", elem_number);
}

void	print_tubes(t_info info)
{
	int		i;
	int		n;
	int		square;

	i = -1;
	ft_printf("\nAnt number : %d[[end]]\n", info.ant_nb);
	ft_printf("[[underline]][[cyan]]This is the adjacence matrix :[[end]]\n");
	ft_printf("%-12s\n", "Room Name :");
	while (++i < info.n + 1)
	{
		n = -1;
		if (i - 1 >= 0)
			ft_printf("%-12s", info.nodelist[i - 1].name);
		else
			ft_printf("%-12s", NULL);
		while (++n < info.n + 1)
		{
			if ((square = info.o_mat[i][n]) && n != i)
				ft_printf("[[green]][[bold]]%d [[end]]", square);
			else if (n != i)
				ft_printf("[[blue]]%d [[end]]", square);
			else
				ft_printf("[[magenta]]%d [[end]]", square);
		}
		ft_printf("\n");
	}
}

void	print_map(t_info info, int to_print)
{
	if (to_print == 1)
		print_rooms(info);
	else
		print_tubes(info);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 16:46:01 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/05 22:54:43 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

int		**queue_create(int n)
{
	int	**queue;
	int	i;

	queue = (int **)malloc(sizeof(int *) * (n + 1));
	i = 0;
	while (i < n + 1)
	{
		queue[i] = 0;
		i++;
	}
	return (queue);
}

void	queue_add_elem(int **queue, int *node)
{
	int	queue_len;

	queue[0] = (int*)((char *)queue[0] + 1);
	queue_len = (int)queue[0];
	queue[queue_len] = node;
}

int		*queue_pick_last(int **queue)
{
	int	queue_len;
	int	*last_elem;

	if (!queue[0])
		return (0);
	queue_len = (int)queue[0];
	last_elem = queue[queue_len];
	queue[queue_len] = 0;
	queue[0] = (int *)((char *)queue[0] - 1);
	return (last_elem);
}

void	queue_print(int **queue, int n)
{
	int	i;

	i = 1;
	while (i < n + 1)
	{
		if (queue[i])
			ft_printf("%2d ", *queue[i]);
		else
			ft_printf(".. ");
		i++;
	}
	ft_printf("\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:27:56 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/28 15:37:40 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_info	store_node_handler(t_info info, t_node new_node)
{
	if (new_node.number >= info.tab_size)
	{
		info.tab_size *= 2;
		info.nodelist = resize_nodelist(info);
		info.hash_table = resize_hashtable(info);
	}
	info.nodelist[info.n] = new_node;
	info.hash_table = hash_insert(info, new_node);
	if (info.end_begin_room)
	{
		if (info.end_begin_room == END)
			info.end_name = new_node.name;
		else
			info.begin_name = new_node.name;
	}
	info.n++;
	return (info);
}

t_node	node_create(char *buf, int node_number)
{
	char	**name_and_pos;
	t_node	new_node;

	new_node.number = node_number;
	new_node.name = NULL;
	name_and_pos = NULL;
	if (buf && !buf[0])
		lemin_error("You passed an empty line in the map");
	if (!(name_and_pos = ft_split_whitespaces(buf)))
		lemin_error("error in split whitespaces in node_create");
	new_node.name = name_and_pos[0];
	new_node.x = ft_atoi(name_and_pos[1]);
	new_node.y = ft_atoi(name_and_pos[2]);
	ft_memdel((void**)&name_and_pos[1]);
	ft_memdel((void**)&name_and_pos[2]);
	ft_memdel((void**)&name_and_pos[3]);
	free(name_and_pos);
	name_and_pos = NULL;
	return (new_node);
}

t_info	create_tubes(t_info info)
{
	int i;
	int	n;
	int	**tubes;

	i = -1;
	tubes = NULL;
	if (!(tubes = malloc(sizeof(int *) * (info.n + 1))))
		lemin_error("malloc error in create_tubes");
	while (++i < info.n + 1)
	{
		tubes[i] = NULL;
		if (!(tubes[i] = malloc(sizeof(int) * (info.n + 1))))
			lemin_error("malloc error in create_tubes");
		n = -1;
		while (++n < info.n + 1)
			tubes[i][n] = 0;
	}
	info.o_mat = tubes;
	return (info);
}

t_info	tube_assign(char *buf, t_info info)
{
	t_node	tube_1;
	t_node	tube_2;
	int		i;
	char	*to_find_1;
	char	*to_find_2;

	to_find_1 = buf;
	i = 0;
	while (buf[i] && buf[i] != '-')
		i++;
	if (buf[i] != '-' || !buf[i])
		lemin_error("error in tube assigning in tube_assign");
	buf[i] = '\0';
	i++;
	to_find_2 = &buf[i];
	tube_1 = hash_retrieve(info, to_find_1);
	tube_2 = hash_retrieve(info, to_find_2);
	if (tube_1.number != tube_2.number)
	{
		info.o_mat[tube_1.number + 1][tube_2.number + 1] = 1;
		info.o_mat[tube_2.number + 1][tube_1.number + 1] = 1;
	}
	return (info);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_end_begin_rooms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:47 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/28 15:38:02 by lazrossi         ###   ########.fr       */
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
		end_begin = hash_retrieve(info, info.end_name);
		swap = info.nodelist[info.n - 1];
		info.nodelist[info.n - 1] = end_begin;
		info.nodelist[end_begin.number] = swap;
	}
	else if (start_or_end == START)
	{
		end_begin = hash_retrieve(info, info.begin_name);
		swap = info.nodelist[0];
		info.nodelist[0] = end_begin;
		info.nodelist[end_begin.number] = swap;
	}
	return (info);
}

t_info			swap_end_begin_room(t_info info, int start_or_end)
{
	t_node		end_begin;
	t_node		swap;
	const char	*name;
	int			tmp_nbr;
	int			where;

	where = (start_or_end == START) ? 0 : info.n - 1;
	name = (start_or_end == START) ?
		info.begin_name : info.end_name;
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
