/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 16:02:14 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/12 22:33:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

int	main()
{
	t_hash_table 	*table;
	t_node			*elem;
	t_node			**elem_table;
	char			test[7] = "coucou";

	table = NULL;
	elem = NULL;
	elem_table = NULL;
	table = create_table();
	create_resize_hashtable(table, DATA_INITIAL_SIZE);
	if (!(elem = malloc(sizeof(t_node))))
		lemin_error("malloc error in main");
	elem->name = ft_strdup(test);
	elem->number = 1;
	hash_insert(table->hash_table, DATA_INITIAL_SIZE, elem); 
	ft_putnbr(hash_retrieve(table->hash_table, test, table->size)->number);
}
