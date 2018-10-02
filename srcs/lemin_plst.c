/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_plst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:44:40 by jboursal          #+#    #+#             */
/*   Updated: 2018/10/02 02:30:33 by lazrossi         ###   ########.fr       */
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
	new_m->nbftot = 0;
	new_m->nbf = 0;
	new_m->first_node = 0;
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

	while (*plst)
	{
		ilstdel(&(*plst)->path);
		tmp = *plst;
		*plst = (*plst)->next;
		ft_memdel((void**)&tmp);
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
