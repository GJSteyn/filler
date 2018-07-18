/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:30:24 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/18 07:44:12 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			valid_pos(t_piece *pc, t_2dvect pos, t_filler *f)
{
	int		x;
	int		count;

	x = -1;
	count = 0;
	if (!piece_fits(f, pos))
		return (0);
	while (++x < pc->dim.x)
	{
		if (x + pos.x < 0 || x + pos.x >= f->map->dim.x)
			continue;
		if (!valid_y_axis(pos, f, x, &count))
			return (0);
	}
	if (count == 1)
		return (1);
	return (0);
}

int			valid_y_axis(t_2dvect pos, t_filler *f, int x, int *count)
{
	char	map_pc;
	int		y;
	t_piece	*pc;

	y = -1;
	pc = f->pc;
	while (++y < pc->dim.y)
	{
		if (y + pos.y < 0 || y + pos.y >= f->map->dim.y)
			continue;
		map_pc = f->map->grid[itop(x + pos.x, y + pos.y, f->map->dim)];
		if (pc->grid[itop(x, y, pc->dim)] == '*' &&
				(map_pc == f->pl->c || map_pc == f->pl->c - 32))
			(*count)++;
		else if (pc->grid[itop(x, y, pc->dim)] == '*' &&
				(map_pc == f->pl->e || map_pc == f->pl->e - 32))
			return (0);
	}
	return (1);
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

t_2dvect	optimal_place(t_filler *f)
{
	int			i;
	int			j;
	int			best;
	int			current;
	t_2dvect	bestplace;

	i = -f->pc->dim.x - 1;
	j = -f->pc->dim.y - 1;
	best = 0;
	current = 0;
	bestplace = itovect(0, 0);
	while (++i < f->map->dim.x + f->pc->dim.x)
	{
		while (++j < f->map->dim.y + f->pc->dim.y)
		{
			if ((current = place_rating(itovect(i, j), f)) >= best)
			{
				best = current;
				bestplace = itovect(i, j);
			}
		}
		j = -f->pc->dim.y - 1;
	}
	return (bestplace);
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
				rating += f->hmap->grid[itop(i + pos.x, j +
						pos.y, f->map->dim)];
		}
		j = -1;
	}
	return (rating);
}
