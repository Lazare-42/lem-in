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
