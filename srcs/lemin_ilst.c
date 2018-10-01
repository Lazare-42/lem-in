/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_ilst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:18:15 by jboursal          #+#    #+#             */
/*   Updated: 2018/10/01 01:46:48 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

t_ilst	*ilstnew(int const n)
{
	t_ilst	*new_m;

	new_m = 0;
	if (!(new_m = (t_ilst*)malloc(sizeof(t_ilst))))
		return (0);
	new_m->n = n;
	new_m->ant_index = 0;
	new_m->next = NULL;
	return (new_m);
}

void	ilstadd(t_ilst **ilst, t_ilst *new_ilst)
{
	new_ilst->next = *ilst;
	*ilst = new_ilst;
}

t_ilst	*ilstrev(t_ilst **head)
{
	t_ilst	*prev;
	t_ilst	*next;
	t_ilst	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}

void	ilstdel(t_ilst **ilst)
{
	t_ilst	*tmp;

	while (*ilst)
	{
		tmp = *ilst;
		*ilst = (*ilst)->next;
		ft_memdel((void**)&tmp);
	}
}

void	ilst_print(t_ilst **ilst)
{
	t_ilst	*tmp;
	int		i;

	tmp = *ilst;
	i = 0;
	while (tmp)
	{
		ft_printf("node %d: %c\n", i, tmp->n + 65);
		tmp = tmp->next;
		i++;
	}
}
