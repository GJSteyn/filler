/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:30:24 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/20 14:08:19 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			ft_itop(int x, int y, t_2dvect dim)
{
	return ((x * dim.y) + y);
}

t_2dvect	ft_itovect(int x, int y)
{
	t_2dvect	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

int			ft_valid_pos(t_piece *piece, t_2dvect pos, t_filler *fill)
{
	int		i;
	int		j;
	int		count;
	char	map_piece;

	i = 0;
	j = 0;
	count = 0;
	while (i < piece->dim.x)
	{
		while (j < piece->dim.y)
		{
			map_piece = fill->map->grid[ft_itop(i + pos.x, j + pos.y, fill->map->dim)];
			if (piece->grid[ft_itop(i, j, piece->dim)] == '*' && (map_piece == fill->player->c || map_piece == fill->player->c - 32))
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

char		*ft_ind_to_str(int x, int y)
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
