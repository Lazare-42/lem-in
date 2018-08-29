/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_visualizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:44:21 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/29 21:26:26 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
void	print_map_visualizer(t_info info)
{
	int i;
	int	j;
	int	fd;

	i = 0;
	fd = open("/Users/lazrossi/Documents/42/lem-in/visualisateur/output.map",
			O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	while (i < info.n)
	{
		ft_dprintf(fd, "%s %d %d", info.nodelist[i].name, info.nodelist[i].x, info.nodelist[i].y);
		j = 0;
		while (j < info.n)
		{
			ft_dprintf(fd, " %d", info.nodelist[i].tubes[j]);
			j++;
		}
		ft_dprintf(fd, "\n");
		i++;
	}
	close(fd);
}
