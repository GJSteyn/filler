/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:30:24 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 12:42:14 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			ft_valid_pos(t_piece *piece, t_2dvect pos, t_filler *fill)
{
	int		i;
	int		j;
	int		count;
	char	map_piece;

	i = -1;
	j = -1;
	count = 0;
	if (!ft_piece_fits(fill, pos))
		return (0);
	while (++i < piece->dim.x)
	{
		if (i + pos.x < 0 || i + pos.x >= fill->map->dim.x)
			continue;
		while (++j < piece->dim.y)
		{
			if (j + pos.y < 0 || j + pos.y >= fill->map->dim.y)
				continue;
			map_piece = fill->map->grid[ft_itop(i + pos.x, j + pos.y, fill->map->dim)];
			if (piece->grid[ft_itop(i, j, piece->dim)] == '*' && (map_piece == fill->player->c || map_piece == fill->player->c - 32))
				count++;
			else if (piece->grid[ft_itop(i, j, piece->dim)] == '*' && (map_piece == fill->player->e || map_piece == fill->player->e - 32))
				return (0);
		}
		j = -1;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

int			ft_piece_fits(t_filler *fill, t_2dvect pos)
{
	int		i;
	int		j;
	int		size;
	int		count;

	i = 0;
	j = 0;
	size = ft_count_stars(fill);
	count = 0;
	while (i < fill->piece->dim.x)
	{
		while (j < fill->piece->dim.y)
		{
			if (fill->piece->grid[ft_itop(i, j, fill->piece->dim)] == '*')
			{
				if (i + pos.x >= 0 && i + pos.x < fill->map->dim.x && j + pos.y >= 0 && j + pos.y < fill->map->dim.y)
					count++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (count == size)
		return (1);
	return (0);
}

int			ft_count_stars(t_filler *fill)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < fill->piece->size)
	{
		if (fill->piece->grid[i] == '*')
			count++;
		i++;
	}
	return (count);
}

int			ft_get_placement_rating(t_2dvect pos, t_filler *fill)
{
	int		i;
	int		j;
	int		rating;

	i = -1;
	j = -1;
	rating = 0;
	if (!ft_valid_pos(fill->piece, pos, fill))
		return (-1);
	while (++i < fill->piece->dim.x)
	{
		if (i + pos.x < 0 || i + pos.x > fill->map->dim.x)
			continue;
		while (++j < fill->piece->dim.y)
		{
			if (j + pos.y < 0 || j + pos.y > fill->map->dim.y)
				continue;
			if (fill->piece->grid[ft_itop(i, j, fill->piece->dim)] == '*')
				rating += fill->hmap->grid[ft_itop(i + pos.x, j + pos.y, fill->map->dim)];
			j++;
		}
		j = -1;
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
