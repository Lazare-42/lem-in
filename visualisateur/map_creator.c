#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lemin.h"

typedef enum    e_type
{
    std, loop_full, deadend_full, uselesspath_full
}               t_type;

/*long long	ft_abs(long long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;

	long_n = n;
	if (long_n < 0)
	{
		ft_putchar_fd('-', fd);
		long_n = ft_abs(long_n);
	}
	if (long_n > 9)
		ft_putnbr_fd(long_n / 10, fd);
	ft_putchar_fd(long_n % 10 + '0', fd);
}*/

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

void    mat_export(int **mat, int node_nb)
{
    int fd;
    int y;
    int x;

    fd = open("output.map", O_CREAT | O_WRONLY);
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
        write(fd, "\r", 1);
        y++;
    }
    close(fd);
}

int     **map_creator(t_type type, int node_nb, int links_percent, int is_valide)
{
    int **mat;

    mat = mat_create(node_nb);
    mat_put_connections(mat, node_nb, links_percent);

    if (type == loop_full)
        mat_put_loop(mat, node_nb);
    else
        mat_remove_loop(mat, node_nb);

    if (is_valide)
        mat_put_path(mat, node_nb);
    else
        mat_remove_path(mat, node_nb);
    mat_export(mat, node_nb);
    return (mat);
}
