/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 21:52:24 by jboursal          #+#    #+#             */
/*   Updated: 2018/08/25 19:06:11 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define GET 0
#define PUT 1

typedef struct  s_node
{
	int         index;
	int         weight;
}               t_node;

Gtypedef struct  s_info
{
	int         n;
	int         **mat;
}               t_info;

int get_from_model(int y, int x)
{
	static int  model[5][5] =
	{
		{0, 1, 0, 1, 0},
		{1, 0, 1, 0, 0},
		{0, 1, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 0, 1, 1, 0},
	};
	return (model[y][x]);
}

int **mat_init(int n)
{
	int **mat;
	int y;
	int x;

	y = 0;
	mat = (int **)malloc(sizeof(int *) * n);
	while (y < n)
	{
		x = 0;
		mat[y] = (int *)malloc(sizeof(int) * n);
		while (x < n)
		{
			mat[y][x] = get_from_model(y, x);
			x++;
		}
		y++;
	}
	return (mat);
}

void mat_print(t_info info)
{
	int y;
	int x;
	int n;

	y = 0;
	n = 5;
	while (y < n)
	{
		x = 0;
		while (x < n)
		{
			printf("%d ", info.mat[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void  to_heap(t_node **heap, t_node node)
{
	int     i;
	t_node  tmp;

	(*heap)[0].index++;
	i = (*heap)[0].index;
	(*heap)[(*heap)[0].index] = node;
	while ((*heap)[i].weight < (*heap)[i / 2].weight && i)
	{
		tmp = (*heap)[i];
		(*heap)[i] = (*heap)[i / 2];
		(*heap)[i / 2] = tmp;
		i /= 2;
	}

	printf("\'%d\' TO_HEAP - SIZE: \'%d\'\n", node.weight, (*heap)[0].index);
	i = 1;
	while (i < (*heap)[0].index + 1)
	{
		printf("index : %d - weight : %d\n", i, (*heap)[i].weight);
		i++;
	}
}

t_node  from_heap(t_node **heap)
{
	int     i;
	t_node  tmp;
	t_node  ret;

	(*heap)[0].index--;
	i = 1;
	ret = (*heap)[1];
	(*heap)[1] = (*heap)[(*heap)[0].index + 1];
	while (((*heap)[i].weight > (*heap)[i / 2].weight || (*heap)[i].weight > (*heap)[i / 2 + 1].weight) && i < (*heap)[0].index)
	{
		tmp = (*heap)[i];
		if ((*heap)[2 * i].weight < (*heap)[2 * i + 1].weight)
		{
			(*heap)[i] = (*heap)[2 * i];
			(*heap)[2 * i] = tmp;
			i = 2 * i;
		}
		else
		{
			(*heap)[i] = (*heap)[2 * i + 1];
			(*heap)[2 * i + 1] = tmp;
			i = 2 * i + 1;
		}
	}

	printf("FROM_HEAP - SIZE: \'%d\'\n", (*heap)[0].index);
	i = 1;
	while (i < (*heap)[0].index + 1)
	{
		printf("index : %d - weight : %d\n", i, (*heap)[i].weight);
		i++;
	}
	return (ret);
}

void    dijkstra(t_info *info)
{
	t_node  *heap;
	heap = (t_node *)malloc(sizeof(t_node) * (info->n + 1));
	int i;

	i = 0;
	t_node node_1;
	t_node node_2;
	t_node node_3;
	t_node node_4;
	t_node node_5;

	node_1.weight = 18;
	node_2.weight = 17;
	node_3.weight = 16;
	node_4.weight = 15;
	node_5.weight = 1;

	to_heap(&heap, node_1);
	to_heap(&heap, node_2);
	to_heap(&heap, node_3);
	to_heap(&heap, node_4);
	to_heap(&heap, node_5);
	printf("weight_1 = %d \n", from_heap(&heap).weight);
	printf("weight_2 = %d \n", from_heap(&heap).weight);
	printf("weight_3 = %d \n", from_heap(&heap).weight);
	printf("weight_4 = %d \n", from_heap(&heap).weight);
	printf("weight_5 = %d \n", from_heap(&heap).weight);
}

int main()
{
	t_info  *info;

	info =(t_info *)malloc(sizeof(t_info) * 1);
	info->n = 5;
	info->mat = mat_init(info->n);
	printf("BEFORE DIJKSTRA\n\n");
	map_print(*info);
	dijkstra(info);

	return 0;
}

