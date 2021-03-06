/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 14:03:10 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/25 20:30:07 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <unistd.h>
#include <fcntl.h>

void	lemin_error(char *error)
{
	int fd;

	fd = open("/Users/lazrossi/Documents/42/lem-in/error_trace.txt",
			O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	ft_dprintf(fd, "%s\n", error);
	close(fd);
	ft_myexit("ERROR");
}
