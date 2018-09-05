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
