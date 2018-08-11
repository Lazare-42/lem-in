/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 14:03:10 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/11 14:04:44 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

void	lemin_error(char *error)
{
	ft_printf("[[~/Documents/42/lem-in/error_trace.txt]]%s\n", error);
	ft_myexit("ERROR");
}
