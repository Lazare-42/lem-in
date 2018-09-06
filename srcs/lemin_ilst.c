/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_ilst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:18:15 by jboursal          #+#    #+#             */
/*   Updated: 2018/09/06 01:19:28 by jboursal         ###   ########.fr       */
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
	new_m->next = NULL;
	return (new_m);
}

void	ilstadd(t_ilst **ilst, t_ilst *new_ilst)
{
	new_ilst->next = *ilst;
	*ilst = new_ilst;
}

void	ilstdel(t_ilst **ilst)
{
	t_ilst	*tmp;

	tmp = *ilst;
	while (*ilst)
	{
		*ilst = tmp->next;
		free(tmp);
		tmp = *ilst;
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
