/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:31:45 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/10 23:45:25 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

int		main(int ac, char **argv)
{
	char	*buf;

	buf = NULL;
	ft_printf("%d is ac\n, %s is argv\n", ac, argv[1]);
	get_next_line(1, &buf, '\n');
	ft_printf("%s is argv\n", buf);
	return (0);
}
