/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 07:19:57 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 14:46:30 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_hmap		*ft_init_hmap(void)
{
	t_hmap		*ret;

	ret = (t_hmap*)malloc(sizeof(t_hmap));
	ret->grid = NULL;
	return (ret);
}

void		ft_gen_hmap(t_filler *f)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!f->hmap->grid)
		f->hmap->grid = (int*)ft_memalloc(sizeof(int) * (f->map->dim.x * f->map->dim.y));
	ft_clear_hmap(f->hmap, f->map->dim.x * f->map->dim.y);
	while (i < f->map->dim.x)
	{
		while (j < f->map->dim.y)
		{
			ft_get_hval(i, j, f);
			j++;
		}
		j = 0;
		i++;
	}
}

void		ft_clear_hmap(t_hmap *hmap, int mapsize)
{
	int		i;

	i = 0;
	while (i < mapsize)
		hmap->grid[i++] = 0;
}

void		ft_get_hval(int x, int y, t_filler *f)
{
	char	*map;
	int		*hmap;
	int		pos;

	map = f->map->grid;
	hmap = f->hmap->grid;
	pos = ft_itop(x, y, f->map->dim);
	if (map[pos] == f->pl->c || map[pos] == f->pl->c - 32 || map[pos] == f->pl->e || map[pos] == f->pl->e - 32)
	{
		hmap[pos] = 0;
		return ;
	}
	ft_hval_top(x, y, f);
	ft_hval_bot(x, y, f);
	ft_hval_level(x, y, f);
}

void		ft_hval_top(int x, int y, t_filler *f)
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
			tmp = map[ft_itop(x - 1, y - 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[ft_itop(x, y, f->map->dim)] = 2;
		}
		tmp = map[ft_itop(x - 1, y, f->map->dim)];
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[ft_itop(x, y, f->map->dim)] = 2;
		if (y < f->map->dim.y - 1)
		{
			tmp = map[ft_itop(x - 1, y + 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[ft_itop(x, y, f->map->dim)] = 2;
		}
	}
}

void		ft_hval_bot(int x, int y, t_filler *f)
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
			tmp = map[ft_itop(x + 1, y - 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[ft_itop(x, y, f->map->dim)] = 2;
		}
		tmp = map[ft_itop(x + 1, y, f->map->dim)];
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[ft_itop(x, y, f->map->dim)] = 2;
		if (y < f->map->dim.y - 1)
		{
			tmp = map[ft_itop(x + 1, y + 1, f->map->dim)];
			if (tmp == f->pl->e || tmp == f->pl->e - 32)
				hmap[ft_itop(x, y, f->map->dim)] = 2;
		}
	}
}

void		ft_hval_level(int x, int y, t_filler *f)
{
	char	*map;
	int		*hmap;
	char	tmp;

	map = f->map->grid;
	hmap = f->hmap->grid;
	if (y > 0)
	{
		tmp = map[ft_itop(x, y - 1, f->map->dim)]; 
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[ft_itop(x, y, f->map->dim)] = 2;
	}
	if (y < f->map->dim.y - 1)
	{
		tmp = map[ft_itop(x, y + 1, f->map->dim)]; 
		if (tmp == f->pl->e || tmp == f->pl->e - 32)
			hmap[ft_itop(x, y, f->map->dim)] = 2;
	}
}

void		ft_print_hmap(t_filler *f)
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

void		ft_diag_alter(t_filler *f)
{
	t_2dvect	cur;

	cur = f->pl->c_start;
	while (cur.x != f->pl->e_start.x || cur.y != f->pl->e_start.y)
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
