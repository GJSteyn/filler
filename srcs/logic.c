/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:30:24 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/18 08:32:04 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_itop(int x, int y, t_2dvect dim)
{
	return ((x * (dim.x - 1)) + y);
}

t_2dvect	ft_itovect(int x, int y)
{
	t_2dvect	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

int		ft_valid_pos(t_piece *piece, t_2dvect pos, t_filler *fill)
{
	int		i;
	int		j;
	int		count;
	char	map_piece;

	i = 0;
	j = 0;
	count = 0;
	while (i < piece->dim.y)
	{
		while (j < piece->dim.x)
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
