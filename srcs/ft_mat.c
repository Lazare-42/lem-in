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
