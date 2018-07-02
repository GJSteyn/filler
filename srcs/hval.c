/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 07:03:27 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/02 07:04:03 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_hval(int x, int y, t_filler *f)
{
	char	*map;
	int		*hmap;
	int		pos;

	map = f->map->grid;
	hmap = f->hmap->grid;
	pos = itop(x, y, f->map->dim);
	if (map[pos] == f->pl->c || map[pos] == f->pl->c - 32 || map[pos] == f->pl->e || map[pos] == f->pl->e - 32)
	{
		hmap[pos] = 0;
		return ;
	}
	hval_top(x, y, f);
	hval_bot(x, y, f);
	hval_level(x, y, f);
}

void		hval_top(int x, int y, t_filler *f)
{
	char	*map;
	int		*hmap;
	char	tmp;

	map = f->map->grid;
	hmap = f->hmap->grid;
	if (x > 0)
	{
		if (y > 0)
		{
			tmp = map[itop(x - 1, y - 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[itop(x, y, f->map->dim)] = 2;
		}
		tmp = map[itop(x - 1, y, f->map->dim)];
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[itop(x, y, f->map->dim)] = 2;
		if (y < f->map->dim.y - 1)
		{
			tmp = map[itop(x - 1, y + 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[itop(x, y, f->map->dim)] = 2;
		}
	}
}

void		hval_bot(int x, int y, t_filler *f)
{
	char	*map;
	int		*hmap;
	char	tmp;

	map = f->map->grid;
	hmap = f->hmap->grid;
	if (x < f->map->dim.x - 1)
	{
		if (y > 0)
		{
			tmp = map[itop(x + 1, y - 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[itop(x, y, f->map->dim)] = 2;
		}
		tmp = map[itop(x + 1, y, f->map->dim)];
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[itop(x, y, f->map->dim)] = 2;
		if (y < f->map->dim.y - 1)
		{
			tmp = map[itop(x + 1, y + 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[itop(x, y, f->map->dim)] = 2;
		}
	}
}

void		hval_level(int x, int y, t_filler *f)
{
	char	*map;
	int		*hmap;
	char	tmp;

	map = f->map->grid;
	hmap = f->hmap->grid;
	if (y > 0)
	{
		tmp = map[itop(x, y - 1, f->map->dim)]; 
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[itop(x, y, f->map->dim)] = 2;
	}
	if (y < f->map->dim.y - 1)
	{
		tmp = map[itop(x, y + 1, f->map->dim)]; 
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[itop(x, y, f->map->dim)] = 2;
	}
}

