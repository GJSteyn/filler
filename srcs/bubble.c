/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 15:07:58 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 15:26:39 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_diag_alter(t_filler *f)
{
	t_2dvect	cur;

	cur = f->pl->c_start;
	while (cur.x != f->pl->e_start.x && cur.y != f->pl->e_start.y)
	{
		if (f->map->grid[ft_itop(cur.x, cur.y, f->map->dim)] == '.')
			f->hmap->grid[ft_itop(cur.x, cur.y, f->map->dim)] += 20;
		if (cur.x < f->pl->e_start.x)
			cur.x += 1;
		else if (cur.x > f->pl->e_start.x)
			cur.x -= 1;
		if (cur.y < f->pl->e_start.y)
			cur.y += 1;
		else if (cur.y > f->pl->e_start.y)
			cur.y -= 1;
	}
}

void		ft_bubble_top(t_filler *f, int i, int x, int y)
{
	if (x >= 0 && x < f->map->dim.x && y >= 0 && y < f->map->dim.y)
	{
		if (f->map->grid[ft_itop(x, y, f->map->dim)] != '.')
			return ;
	}
	if (x > 0)
	{
		if (f->map->grid[ft_itop(x - 1, y, f->map->dim)] == f->pl->c)
			return ;
		if (f->map->grid[ft_itop(x - 1, y, f->map->dim)] == f->pl->c - 32)
			return ;
		if (f->hmap->grid[ft_itop(x - 1, y, f->map->dim)] == i)
			f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
		if (y > 0)
		{
			if (f->map->grid[ft_itop(x - 1, y - 1, f->map->dim)] == f->pl->c)
				return ;
			if (f->map->grid[ft_itop(x - 1, y - 1, f->map->dim)] == f->pl->c - 32)
				return ;
			if (f->hmap->grid[ft_itop(x - 1, y - 1, f->map->dim)] == i)
				f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
		}
		if (y < f->map->dim.y - 1)
		{
			if (f->hmap->grid[ft_itop(x - 1, y + 1, f->map->dim)] == i)
				f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
		}
	}
}

void		ft_bubble_bot(t_filler *f, int i, int x, int y)
{
	if (x >= 0 && x < f->map->dim.x && y >= 0 && y < f->map->dim.y)
	{
		if (f->map->grid[ft_itop(x, y, f->map->dim)] != '.')
			return ;
	}
	if (x < f->map->dim.x - 1)
	{
		if (f->hmap->grid[ft_itop(x + 1, y, f->map->dim)] == i)
			f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
		if (y > 0)
		{
			if (f->hmap->grid[ft_itop(x + 1, y - 1, f->map->dim)] == i)
				f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
		}
		if (y < f->map->dim.y - 1)
		{
			if (f->hmap->grid[ft_itop(x + 1, y + 1, f->map->dim)] == i)
				f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
		}
	}
}

void		ft_bubble_level(t_filler *f, int i, int x, int y)
{
	if (y >= 0 && y < f->map->dim.y)
	{
		if (f->map->grid[ft_itop(x, y, f->map->dim)] != '.')
			return ;
	}
	if (y > 0)
	{
		if (f->hmap->grid[ft_itop(x, y - 1, f->map->dim)] == i)
			f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
	}
	if (y < f->map->dim.y - 1)
	{
		if (f->hmap->grid[ft_itop(x, y + 1, f->map->dim)] == i)
			f->hmap->grid[ft_itop(x, y, f->map->dim)] = i + 1;
	}
}

void		ft_bubble(t_filler *f)
{
	int		i;
	int		x;
	int		y;
	int		target;

	i = 1;
	x = 0;
	y = 0;
	target = ft_get_target(f);
	while (i < target)
	{
		while (x < f->map->dim.x)
		{
			while (y < f->map->dim.y)
			{
				if (f->hmap->grid[ft_itop(x, y, f->map->dim)] == 0)
				{
					ft_bubble_top(f, i, x, y);
					ft_bubble_bot(f, i, x, y);
					ft_bubble_level(f, i, x, y);
				}
				y++;
			}
			y = 0;
			x++;
		}
		x = 0;
		i++;
	}
}

int			ft_get_target(t_filler *f)
{
	if (f->map->dim.x == 100)
		return (5);
	if (f->map->dim.x == 24)
		return (3);
	else
		return (2);
}
