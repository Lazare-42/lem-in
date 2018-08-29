/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:08:31 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/25 20:08:51 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** the fonction parse stores the string argument
** in a string in a structure of a linked list.
** If it meets an argument it
** sends the structure and the va_list element
** to the function treat_and_store elements which stores all required elements
** (width, precision, argument itself) in the structure and eventually sends
** the structure and its element to the precision and width handler,
** apply_precision_width
** If any error is encoutered set_get_return is set to -1. Else the function
** ft_printf returns from the write function in print_list()
*/

#include "../includes/libft.h"
#include <unistd.h>

int			ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list		ap;
	int			return_val;
	t_str		argument_str;

	return_val = -1;
	set_get_fd(fd);
	if (!(format))
	{
		ft_putstr_fd("Please stop fooling around with my ft_printf.", 2);
		return (-1);
	}
	va_start(ap, format);
	return_val = launch_string_print(format, ap, &argument_str, 0);
	va_end(ap);
	return (return_val);
}
