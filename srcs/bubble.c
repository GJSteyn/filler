/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 15:07:58 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/02 09:51:35 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		bubble_top(t_filler *f, int i, int x, int y)
{
	if (x >= 0 && x < f->map->dim.x && y >= 0 && y < f->map->dim.y)
	{
		if (f->map->grid[itop(x, y, f->map->dim)] != '.')
			return ;
	}
	if (x > 0)
	{
		if (f->map->grid[itop(x - 1, y, f->map->dim)] == f->pl->c ||
				f->map->grid[itop(x - 1, y, f->map->dim)] == f->pl->c - 32)
			return ;
		if (f->hmap->grid[itop(x - 1, y, f->map->dim)] == i)
			f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
		if (y > 0)
		{
			if (f->map->grid[itop(x - 1, y - 1, f->map->dim)] == f->pl->c)
				return ;
			if (f->map->grid[itop(x - 1, y - 1, f->map->dim)] == f->pl->c - 32)
				return ;
			if (f->hmap->grid[itop(x - 1, y - 1, f->map->dim)] == i)
				f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
		}
		if (y < f->map->dim.y - 1)
			if (f->hmap->grid[itop(x - 1, y + 1, f->map->dim)] == i)
				f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
	}
}

void		bubble_bot(t_filler *f, int i, int x, int y)
{
	if (x >= 0 && x < f->map->dim.x && y >= 0 && y < f->map->dim.y)
	{
		if (f->map->grid[itop(x, y, f->map->dim)] != '.')
			return ;
	}
	if (x < f->map->dim.x - 1)
	{
		if (f->hmap->grid[itop(x + 1, y, f->map->dim)] == i)
			f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
		if (y > 0)
		{
			if (f->hmap->grid[itop(x + 1, y - 1, f->map->dim)] == i)
				f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
		}
		if (y < f->map->dim.y - 1)
		{
			if (f->hmap->grid[itop(x + 1, y + 1, f->map->dim)] == i)
				f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
		}
	}
}

void		bubble_level(t_filler *f, int i, int x, int y)
{
	if (y >= 0 && y < f->map->dim.y)
	{
		if (f->map->grid[itop(x, y, f->map->dim)] != '.')
			return ;
	}
	if (y > 0)
	{
		if (f->hmap->grid[itop(x, y - 1, f->map->dim)] == i)
			f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
	}
	if (y < f->map->dim.y - 1)
	{
		if (f->hmap->grid[itop(x, y + 1, f->map->dim)] == i)
			f->hmap->grid[itop(x, y, f->map->dim)] = i + 1;
	}
}

void		bubble(t_filler *f)
{
	int		i;
	int		x;
	int		y;
	int		target;

	i = 1;
	target = get_target(f);
	while (i < target)
	{
		x = -1;
		while (++x < f->map->dim.x)
		{
			y = -1;
			while (++y < f->map->dim.y)
			{
				if (f->hmap->grid[itop(x, y, f->map->dim)] == 0)
				{
					bubble_top(f, i, x, y);
					bubble_bot(f, i, x, y);
					bubble_level(f, i, x, y);
				}
			}
		}
		i++;
	}
}

int			get_target(t_filler *f)
{
	if (f->map->dim.x == 100)
		return (5);
	if (f->map->dim.x == 24)
		return (3);
	else
		return (2);
}
