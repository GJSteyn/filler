#include "filler.h"

void	ft_vert_alter(t_filler *fill)
{
	t_2dvect	cur;

	cur = fill->pl->c_start;
	while (cur.x >= 0 && cur.x < fill->map->dim.x)
	{
		fill->hmap->grid[itop(cur.x, cur.y, fill->map->dim)] += 15;
		if (fill->pl->c_start.x >= fill->pl->e_start.x)
			cur.x -= 1;
		else
			cur.x += 1;
	}
}
