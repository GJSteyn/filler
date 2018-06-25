/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:30:24 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/25 17:35:49 by gsteyn           ###   ########.fr       */
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

t_2dvect	ft_postovect(int x, t_2dvect dim)
{
	t_2dvect	ret;

	ret.x = x / dim.y;
	ret.y = x % dim.y;
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
			else if (piece->grid[ft_itop(i, j, piece->dim)] == '*' && (map_piece == fill->player->e || map_piece == fill->player->e - 32))
				return (0);
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

int		ft_get_placement_rating(t_2dvect pos, t_filler *fill)
{
	int		i;
	int		j;
	int		rating;

	i = 0;
	j = 0;
	rating = 0;
	if (!ft_valid_pos(fill->piece, pos, fill))
		return (-1);
	while (i < fill->piece->dim.x)
	{
		while (j < fill->piece->dim.y)
		{
			if (fill->piece->grid[ft_itop(i, j, fill->piece->dim)] == '*')
				rating += fill->hmap->grid[ft_itop(i + pos.x, j + pos.y, fill->map->dim)];
			j++;
		}
		j = 0;
		i++;
	}
	return (rating);
}

void		ft_get_initial_pos(t_filler *fill)
{
	int			i;

	i = 0;
	while (i < fill->map->size)
	{
		if (fill->map->grid[i] == fill->player->c - 32)
			fill->player->c_start = ft_postovect(i, fill->map->dim);
		else if (fill->map->grid[i] == fill->player->e - 32)
			fill->player->e_start = ft_postovect(i, fill->map->dim);
		i++;
	}
}
