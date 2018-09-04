/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 16:26:03 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/04 21:18:28 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../includes/lemin.h"
#include "../libft/includes/libft.h"


int		**mat_create(int n)
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
			mat[y][x] = 0;
			x++;
		}
		y++;
	}
	return (mat);
}

void    mat_put_connections(int **mat, int node_nb, int links_percent)
{
    int y;
    int x;
    int random_nb;

    y = 0;
	srand(time(NULL));
    while (y < node_nb)
    {
        x = 0;
        while (x < node_nb)
        {
            random_nb = rand();
            if (random_nb % 100 + 1 > (100 - links_percent))
            {
                mat[y][x] = 1;
                mat[x][y] = 1;
            }
            x++;
        }
        y++;
    }
}

void    mat_put_loop(int **mat, int node_nb)
{
    int i;

    i = 0;
    while (i < node_nb)
    {
        mat[i][i] = 1;
        i++;
    }
}

void    mat_remove_loop(int **mat, int node_nb)
{
    int i;

    i = 0;
    while (i < node_nb)
    {
        mat[i][i] = 0;
        i++;
    }
}

void    mat_put_path(int **mat, int node_nb)
{
    int i;

    i = 0;
    while (i < node_nb)
    {
        if (i > 0)
            mat[i][ i - 1] = 1;
        if (i < node_nb - 1)
            mat[i][i + 1] = 1;
        i++;
    }
}

void    mat_remove_path(int **mat, int node_nb)
{
    int i;

    i = 0;
    while (i < node_nb)
    {
        mat[i][node_nb - 1] = 0;
        mat[node_nb - 1][i] = 0;
        i++;
    }
}

void    mat_export(int **mat, int node_nb, char *path)
{
    int fd;
    int y;
    int x;

    fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    y = 0;
    while (y < node_nb)
    {
        ft_putnbr_fd(y, fd);
        write(fd, " ", 1);
        ft_putnbr_fd(y % (int)(ceil(sqrt(node_nb))), fd);
        write(fd, " ", 1);
        ft_putnbr_fd(floor(y / (floor(sqrt(node_nb)))), fd);
        write(fd, " ", 1);
        x = 0;
        while (x < node_nb)
        {
            ft_putnbr_fd(mat[y][x], fd);
            write(fd, " ", 1);
            x++;
        }
        write(fd, "\n", 1);
        y++;
    }
    close(fd);
}

int     **map_creator(t_map_creator map_creator_info, char *path)
{
    int **mat;

    mat = mat_create(map_creator_info.node_nb);
    mat_put_connections(mat, map_creator_info.node_nb, map_creator_info.links_percent);

    if (map_creator_info.type == loop_full)
        mat_put_loop(mat, map_creator_info.node_nb);
    else
        mat_remove_loop(mat, map_creator_info.node_nb);

    if (map_creator_info.is_valide)
        mat_put_path(mat, map_creator_info.node_nb);
    else
        mat_remove_path(mat, map_creator_info.node_nb);
    mat_export(mat, map_creator_info.node_nb, path);
    return (mat);
}
