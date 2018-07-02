/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 07:19:57 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/02 09:22:00 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_hmap		*init_hmap(void)
{
	t_hmap		*ret;

	ret = (t_hmap*)malloc(sizeof(t_hmap));
	ret->grid = NULL;
	return (ret);
}

void		gen_hmap(t_filler *f)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!f->hmap->grid)
		f->hmap->grid = (int*)ft_memalloc(sizeof(int) *
				(f->map->dim.x * f->map->dim.y));
	clear_hmap(f->hmap, f->map->dim.x * f->map->dim.y);
	while (i < f->map->dim.x)
	{
		while (j < f->map->dim.y)
		{
			get_hval(i, j, f);
			j++;
		}
		j = 0;
		i++;
	}
}

void		clear_hmap(t_hmap *hmap, int mapsize)
{
	int		i;

	i = 0;
	while (i < mapsize)
		hmap->grid[i++] = 0;
}

void		print_hmap(t_filler *f)
{
	int		i;
	int		mapsize;

	i = 0;
	mapsize = f->map->dim.x * f->map->dim.y;
	while (i < mapsize)
	{
		ft_putnbr_fd(f->hmap->grid[i], 2);
		if (i % f->map->dim.y == 0)
			ft_putchar_fd('\n', 2);
		i++;
	}
}

void		diag_alter(t_filler *f)
{
	t_2dvect	cur;

	cur = f->pl->c_start;
	while (cur.x != f->pl->e_start.x || cur.y != f->pl->e_start.y)
	{
		if (f->map->grid[itop(cur.x, cur.y, f->map->dim)] == '.')
			f->hmap->grid[itop(cur.x, cur.y, f->map->dim)] += 20;
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
