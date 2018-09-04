/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_visualizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:44:21 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/04 18:01:35 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <fcntl.h>
#include <unistd.h>

void	print_map_visualizer(t_info info, char *path)
{
	int i;
	int	j;
	int	fd;

	i = 0;
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
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
