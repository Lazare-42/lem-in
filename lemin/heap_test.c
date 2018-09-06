/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 21:07:31 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/06 22:26:18 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	heap_print(t_node *heap)
{
	int	i;

	i = 1;
	printf("\033[31mHEAP\n\033[0m");
	while (i < heap[0].index + 1)
	{
		printf(" %03d | node.index : %03d | node.weight : %03d\n", i,
			heap[i].index, heap[i].weight);
		i++;
	}
}

t_node	*heap_create(int n)
{
	t_node	*heap;

	if (!(heap = (t_node *)malloc(sizeof(t_node) * n)))
		return (0);
	heap[0].index = 0;
	return (heap);
}

void	heap_add(t_node *heap, t_node node)
{
	int		i;
	t_node	tmp;

	heap[0].index++;
	i = heap[0].index;
	heap[i] = node;
	while (i && heap[i].weight < heap[i / 2].weight)
	{
		tmp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = tmp;
		i /= 2;
	}
}

t_node	heap_pick_first(t_node *heap)
{
	int		i;
	t_node	tmp;
	t_node	ret;

	i = 1;
	ret = heap[1];
	heap[1] = heap[heap[0].index--];
	while ((heap[i].weight > heap[i / 2].weight || heap[i].weight
		> heap[i / 2 + 1].weight) && i < heap[0].index)
	{
		tmp = heap[i];
		if (heap[2 * i].weight < heap[2 * i + 1].weight)
		{
			heap[i] = heap[2 * i];
			heap[2 * i] = tmp;
			i = 2 * i;
		}
		else
		{
			heap[i] = heap[2 * i + 1];
			heap[2 * i + 1] = tmp;
			i = 2 * i + 1;
		}
	}
	return (ret);
}
