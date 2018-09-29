/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:36:19 by lazrossi          #+#    #+#             */
/*   Updated: 2018/09/29 19:00:57 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"

int	debug(void)
{
	static int nbr = 0;

	nbr++;
	ft_putstr("Debug");
	ft_putchar(' ');
	ft_putnbr(nbr);
	ft_putchar('\n');
	return (nbr);
}
