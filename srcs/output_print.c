/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 03:58:24 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/18 17:05:55 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <math.h>

static void	nbfpp_add(t_best_paths *best_paths, int ant_nb)
{
	t_plst	*plst;
	int		time;
	int		nbftot;

	plst = best_paths->plst;
	time = ceil(best_paths->time);
	while (plst)
	{
		nbftot = time - plst->path_len + 1;
		if (ant_nb > nbftot)
		{
			plst->nbftot = nbftot;
			ant_nb -= nbftot;
		}
		else
		{
			plst->nbftot = ant_nb;
			ant_nb = 0;
		}
		plst = plst->next;
	}
}

static void	path_reverse(t_best_paths *best_paths)
{
	t_plst	*plst;

	plst = best_paths->plst;
	while (plst)
	{
		plst->first_node = plst->path;
		plst->path = ilstrev(&(plst->path));
		plst = plst->next;
	}
}

static void	ilst_move(t_ilst *ilst, t_info info)
{
	(void)info;
	while (ilst)
	{
		if (ilst->next)
		{
		if (ilst->next->ant_index)
			{
				ilst->ant_index = ilst->next->ant_index;
				ilst->next->ant_index = 0;
				ft_printf("L%d-%s ", ilst->ant_index, info.nodelist[ilst->n].name);
			}
		}
		ilst = ilst->next;
	}
}

static void	move_print(t_best_paths *best_paths, t_info info)
{
	int		time;
	int		time_tot;
	int		new_ant_index;
	t_plst	*plst;

	time = 0;
	time_tot = ceil(best_paths->time);
	new_ant_index = 0;
	while (time < time_tot)
	{
		plst = best_paths->plst;
		while (plst)
		{
			if (plst->nbftot)
			{
				new_ant_index++;
				plst->first_node->ant_index = new_ant_index;
				plst->nbftot--;
			}
			ilst_move(plst->path, info);
			plst = plst->next;
		}
		ft_printf("\n");
		time++;
	}
}

void	output_print(t_best_paths *best_paths, t_info *info)
{
	nbfpp_add(best_paths, info->ant_nb);
	path_reverse(best_paths);
	move_print(best_paths, *info);
}
