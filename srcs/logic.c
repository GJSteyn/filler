/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:30:24 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 15:51:12 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			valid_pos(t_piece *pc, t_2dvect pos, t_filler *f)
{
	int		i;
	int		j;
	int		count;
	char	map_pc;

	i = -1;
	j = -1;
	count = 0;
	if (!piece_fits(f, pos))
		return (0);
	while (++i < pc->dim.x)
	{
		if (i + pos.x < 0 || i + pos.x >= f->map->dim.x)
			continue;
		while (++j < pc->dim.y)
		{
			if (j + pos.y < 0 || j + pos.y >= f->map->dim.y)
				continue;
			map_pc = f->map->grid[itop(i + pos.x, j + pos.y, f->map->dim)];
			if (pc->grid[itop(i, j, pc->dim)] == '*' && (map_pc == f->pl->c || map_pc == f->pl->c - 32))
				count++;
			else if (pc->grid[itop(i, j, pc->dim)] == '*' && (map_pc == f->pl->e || map_pc == f->pl->e - 32))
				return (0);
		}
		j = -1;
	}
	if (count == 1)
		return (1);
	return (0);
}

int			piece_fits(t_filler *f, t_2dvect pos)
{
	int		i;
	int		j;
	int		size;
	int		count;

	i = -1;
	j = -1;
	size = count_stars(f);
	count = 0;
	while (++i < f->pc->dim.x)
	{
		while (++j < f->pc->dim.y)
		{
			if (f->pc->grid[itop(i, j, f->pc->dim)] == '*')
			{
				if (i + pos.x >= 0 && i + pos.x < f->map->dim.x
						&& j + pos.y >= 0 && j + pos.y < f->map->dim.y)
					count++;
			}
		}
		j = -1;
	}
	if (count == size)
		return (1);
	return (0);
}

int			count_stars(t_filler *f)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < f->pc->size)
	{
		if (f->pc->grid[i] == '*')
			count++;
		i++;
	}
	return (count);
}

int			place_rating(t_2dvect pos, t_filler *f)
{
	int		i;
	int		j;
	int		rating;

	i = -1;
	j = -1;
	rating = 0;
	if (!valid_pos(f->pc, pos, f))
		return (-1);
	while (++i < f->pc->dim.x)
	{
		if (i + pos.x < 0 || i + pos.x > f->map->dim.x)
			continue;
		while (++j < f->pc->dim.y)
		{
			if (j + pos.y < 0 || j + pos.y > f->map->dim.y)
				continue;
			if (f->pc->grid[itop(i, j, f->pc->dim)] == '*')
				rating += f->hmap->grid[itop(i + pos.x, j + pos.y, f->map->dim)];
		}
		j = -1;
	}
	return (rating);
}

void		get_initial_pos(t_filler *f)
{
	int			i;

	i = 0;
	while (i < f->map->size)
	{
		if (f->map->grid[i] == f->pl->c - 32)
			f->pl->c_start = postovect(i, f->map->dim);
		else if (f->map->grid[i] == f->pl->e - 32)
			f->pl->e_start = postovect(i, f->map->dim);
		i++;
	}
}
