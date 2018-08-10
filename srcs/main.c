/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:24:20 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/11 00:15:46 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

t_node	*parse_map(char **argv)
{
	t_node	*linked_list;
	char	*buf;
	int		ret;

	linked_list = NULL;
	ret = 1;
	while ((ret = get_next_line(0, &buf, '\n')))
	{
		if (ret == -1)
			ft_myexit("ERROR : malloc error");
		if (ft_strstr(buf, "##start"))

	}

}

int		main(int argc, char **argv)
{
	t_node	*linked_list;

	linked_list = NULL;
	if (argc != 2)
		ft_myexit("ERROR");
	if (!(linked_list = parse_map(argv)))
		ft_myexit("ERROR");
	return (1);
}
