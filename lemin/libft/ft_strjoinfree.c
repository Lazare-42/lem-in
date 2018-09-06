/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 20:25:10 by jboursal          #+#    #+#             */
/*   Updated: 2018/07/09 20:35:22 by jboursal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char **s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (!*s1 || !s2)
		return (0);
	if (!(str = ft_strnew(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2)))))
		return (0);
	while ((*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	while (s2[i2])
	{
		str[i + i2] = s2[i2];
		i2++;
	}
	str[i + i2] = 0;
	free(*s1);
	return (str);
}