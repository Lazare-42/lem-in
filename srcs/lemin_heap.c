/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 22:34:22 by jboursal          #+#    #+#             */
/*   Updated: 2018/10/02 02:28:23 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

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
			break ;
	}
	return (i);
}

int		l_heap_pick_first_loop(int ***heap, int *i, int **tmp)
{
	(*tmp) = (*heap)[(*i)];
	if ((*heap)[2 * (*i)][0] < (*heap)[2 * (*i) + 1][0])
	{
		(*heap)[(*i)] = (*heap)[2 * (*i)];
		(*heap)[2 * (*i)] = (*tmp);
		(*i) = 2 * (*i);
	}
	else if ((*i) * 2 + 1 < (*heap)[0][0])
	{
		(*heap)[(*i)] = (*heap)[2 * (*i) + 1];
		(*heap)[2 * (*i) + 1] = (*tmp);
		(*i) = 2 * (*i) + 1;
	}
	else
		return (1);
	return (0);
}

int		*l_heap_pick_first(int **heap)
{
	int		i;
	int		*tmp;
	int		*ret;
	int		check_break;

	i = 1;
	if (!heap[0][0])
		return (0);
	ret = heap[1];
	heap[1] = heap[heap[0][0]--];
	check_break = 0;
	while (((i * 2 < heap[0][0] && heap[i][0] > heap[i * 2][0]) ||
				(i * 2 + 1 < heap[0][0] && heap[i][0]
				> heap[i * 2 + 1][0])) && !check_break)
		check_break = l_heap_pick_first_loop(&heap, &i, &tmp);
	return (ret);
}
