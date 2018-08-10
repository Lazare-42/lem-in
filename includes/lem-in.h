/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:48:16 by lazrossi          #+#    #+#             */
/*   Updated: 2018/08/10 23:08:55 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM-IN_H
# define LEM-IN_H

typedef	struct		s_node t_node;

typedef	struct		s_node
{
	int				**path_marker;
	t_node			**links; 	
}					t_node;

#endif
