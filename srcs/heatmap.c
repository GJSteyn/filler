#include "filler.h"

void		ft_gen_hmap(t_filler *fill)
{
	int		i;
	int		j;
	char	*mapgrid;

	i = 0;
	j = 0;
	if (!fill->hmap->grid)
		fill->hmap->grid = (int*)ft_memalloc(sizeof(int) * (fill->map->dim.x * fill->map->dim.y));
	mapgrid = fill->map->grid;
	ft_clear_hmap(fill->hmap, fill->map->dim.x * fill->map->dim.y);
	while (i < fill->map->dim.x)
	{
		while (j < fill->map->dim.y)
		{
			ft_get_hval(i, j, fill);
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
		hmap[i++] = 0;
}

void		ft_get_hval(int x, int y, t_filler *fill)
{
	char	*map;
	char	*hmap;
	int		pos;

	map = fill->map->grid;
	hmap = fill->hmap->grid;
	pos = ft_itop(x, y, fill->map->dim);
	if (map[pos] == fill->player->c || map[pos] == fill->player->c - 32 || map[pos] == fill->player->e || map[pos] == fill->player->e - 32)
	{
		hmap[pos] = 0;
		return;
	}
	if (x > 0)		// check top row only when there is a top row
	{
		if (y > 0)		// only when there is a left column
		{
			if (map[ft_itop(x - 1, y - 1, fill->map->dim)] != '.')		// check top left
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
		if (map[ft_itop(x - 1, y, fill->map->dim)] != '.')		// check top center
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
		if (y < fill->map->dim.y - 1)		// only when there is a right column
		{
			if (map[ft_itop(x - 1, y + 1, fill->map->dim)] != '.')		// check top right
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
	}
	if (x < fill->map->dim.x - 1)		// check bottom row only when there is a bottom row
	{
		if (y > 0)		// only when there is a left column
		{
			if (map[ft_itop(x + 1, y - 1, fill->map->dim)] != '.')		// check bottom left
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
		if (map[ft_itop(x + 1, y, fill->map->dim)] != '.')		// check bottom center
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
		if (y < fill->map->dim.y - 1)		// only when there is a right column
		{
			if (map[ft_itop(x + 1, y + 1, fill->map->dim)] != '.')		// check bottom right
				hmap[ft_itop(x, y, fill->map->dim)] += 1;
		}
	}
	if (y > 0)		// check left block only when there is a left block
	{
		if (map[ft_itop(x, y - 1, fill->map->dim)] != '.')
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
	}
	if (y < fill->map->dim.y - 1)		// check right block only when there is a right block
	{
		if (map[ft_itop(x, y + 1, fill->map->dim)] != '.')
			hmap[ft_itop(x, y, fill->map->dim)] += 1;
	}
}
