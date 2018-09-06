#include <stdio.h>
#include <stdlib.h>

#define GET 0
#define PUT 1

typedef struct  s_node
{
    int         index;
    int         weight;
}               t_node;

typedef struct  s_info
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

void map_print(t_info info)
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
}

t_node  from_heap(t_node **heap)
{
    int     i;
    t_node  tmp;
    t_node  ret;

    (*heap)[0].index--;
    i = 1;
    ret = (*heap)[1];
    (*heap)[1] = (*heap)[(*heap)[0].index];
    while (((*heap)[i].weight > (*heap)[i / 2].weight || (*heap)[i].weight > (*heap)[i / 2 + 1].weight) && i < (*heap)[0].index)
    {
        tmp = (*heap)[i];
        if ((*heap)[2 * i].weight > (*heap)[2 * i + 1].weight)
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

    node_1.weight = 5;
    node_2.weight = 2;
    node_3.weight = 50;

    to_heap(&heap, node_1);
    to_heap(&heap, node_2);
    to_heap(&heap, node_3);
    printf("plop");
    printf("weight_1 = %d \n", from_heap(&heap).weight);
    printf("weight_2 = %d \n", from_heap(&heap).weight);
    printf("weight_3 = %d \n", from_heap(&heap).weight);
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
