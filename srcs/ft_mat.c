/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:59:12 by jboursal          #+#    #+#             */
/*   Updated: 2018/10/02 01:50:13 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	mat_free(int ***mat, int size)
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
