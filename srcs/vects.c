/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vects.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 12:39:02 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/18 07:57:38 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			itop(int x, int y, t_2dvect dim)
{
	return ((x * dim.y) + y);
}

t_2dvect	itovect(int x, int y)
{
	t_2dvect	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_2dvect	postovect(int x, t_2dvect dim)
{
	t_2dvect	ret;

	ret.x = x / dim.y;
	ret.y = x % dim.y;
	return (ret);
}

char		*ind_to_str(int x, int y)
{
	char	*str1;
	char	*str2;
	char	*temp;

	str1 = ft_itoa(x);
	str2 = ft_itoa(y);
	temp = ft_strjoin(str1, " ");
	ft_strdel(&str1);
	str1 = ft_strjoin(temp, str2);
	ft_strdel(&str2);
	str2 = ft_strjoin(str1, "\n");
	ft_strdel(&temp);
	ft_strdel(&str1);
	return (str2);
}
