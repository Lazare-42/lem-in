#include "lemin.h"

int     get_tab_elem_number(int *tab, int n)
{
    int i;
    int elem_number;

    i = 1;
    elem_number = 0;
    while (i < n)
    {
        if (tab[i])
            elem_number++;
        i++;
    }
    return (elem_number);
}

int     graph_link_counter(int **mat, int n)
{
    int y;
    int useless_node_left;

    y = 1;
    useless_node_left = 0;
    while (y < n + 1)
    {
        mat[y][0] = get_tab_elem_number(mat[y], n + 1);
        if (y > 1 && y < n && mat[y][0] <= 2 && mat[y][0] > 0)
            useless_node_left++;
        y++;
    }
    return (useless_node_left);
}

void    graph_loop_remove(int **mat, int n)
{
    int i;

    i = 1;
    while (i < n + 1)
    {
        mat[i][i] = 0;
        i++;
    }
}

void    graph_dead_end_remove(int **mat, int n)
{
    int dead_end_left;
    int y;
    int x;

    dead_end_left = 1;
    while (dead_end_left)
    {
        y = 2;
        dead_end_left = 0;
        while (y < n)
        {
            if (mat[y][0] == 1)
            {
                dead_end_left = 1;
                mat[y][0] = 0;
                x = 1;
                while (x < n + 1)
                {
                    if (mat[y][x])
                    {
                        mat[x][y] = 0;
                        mat[x][0] = (mat[x][0]) ? mat[x][0]-- : 0;
                        mat[y][x] = 0;
                        break;
                    }
                    x++;
                }
            }
            y++;
        }
    }
}

void    graph_useless_node_remove(int **mat, int n)
{
    int y;
    int x;
    int parent_index;

    y = 2;
    while (y < n)
    {
        if (mat[y][0] == 2)
        {
            mat[y][0] = 0;
            x = 1;
            parent_index = 0;
            while (x < n + 1)
            {
                if (mat[y][x])
                {
                    if (!parent_index)
                    {
                        parent_index = x;
                    }
                    else
                    {
                        if (mat[parent_index][x] == 0 || mat[parent_index][x] > mat[y][parent_index] + mat[y][x])
                        {
                            mat[parent_index][x] = mat[y][parent_index] + mat[y][x];
                            mat[x][parent_index] = mat[y][parent_index] + mat[y][x];
                        }
                        mat[parent_index][y] = 0;
                        mat[x][y] = 0;
                        mat[y][parent_index] = 0;
                        mat[y][x] = 0;
                    }
                }
                x++;
            }
        }
        y++;
    }
}

void    graph_orientation(int **mat, int n)
{
    int y;
    int x;

    y = 1;
    while (y < n + 1)
    {
        x = 1;
        while (x < n + 1)
        {
            if (mat[y][x] && mat[y][0] < mat[x][0])
            {
                mat[y][x] = 0;
            }
            x++;
        }
        y++;
    }
}

void    mat_init_for_dijkstra(int **mat, int n)
{
    int y;

    y = 1;
    while (y < n + 1)
    {
        mat[y][0] = 99;
        y++;
    }
    mat[n][0] = 0;
}
