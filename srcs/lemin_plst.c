/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_plst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:44:40 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/06 01:21:29 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_plst	*plstnew(t_ilst *path)
{
	t_plst	*new_m;

	new_m = 0;
	if (!(new_m = (t_plst*)malloc(sizeof(t_plst))))
		return (0);
	new_m->path = path;
	new_m->path_len = 0;
	new_m->next = NULL;
	return (new_m);
}

void	plstadd(t_plst **plst, t_plst *new_plst)
{
	new_plst->next = *plst;
	*plst = new_plst;
}

void	plstdel(t_plst **plst)
{
	t_plst	*tmp;

	tmp = *plst;
	while (*plst)
	{
		*plst = tmp->next;
		free(tmp);
		tmp = *plst;
	}
}

int		plst_get_len(t_plst **plst)
{
	t_plst	*tmp;
	int		len;

	tmp = *plst;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

void	plst_print(t_plst **plst)
{
	t_plst	*tmp;
	int		i;

	tmp = *plst;
	i = 0;
	while (tmp)
	{
		printf("\nCHEMIN %d - LEN %d\n\n", i, tmp->path_len);
		ilst_print(&(tmp->path));
		tmp = tmp->next;
		i++;
	}
}
