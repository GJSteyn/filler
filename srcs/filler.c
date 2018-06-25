#include "filler.h"

t_filler	*ft_new_filler(void)
{
	t_filler	*ret;

	ret = (t_filler*)malloc(sizeof(t_filler));
	if (!ret)
		ft_putstr_fd("fill mallerror\n", 2);
	ret->player = (t_player*)malloc(sizeof(t_player));
	if (!ret->player)
		ft_putstr_fd("player mallerror\n", 2);
	ret->map = ft_init_map();
	if (!ret->map)
		ft_putstr_fd("map mallerror\n", 2);
	ret->piece = ft_init_piece();
	if (!ret->piece)
		ft_putstr_fd("piece mallerror\n", 2);
	ret->hmap = ft_init_hmap();
	if (!ret->hmap)
		ft_putstr_fd("hmap mallerror\n", 2);
	return (ret);
}

void		ft_filler(t_filler *fill)
{
	int		i;
	int		j;
	int		best;
	int		current;
	t_2dvect	bestplace;
	char	*temp;

	i = 0;
	j = 0;
	best = 0;
	current = 0;
	bestplace = ft_itovect(0, 0);
	ft_get_info(fill);
	ft_gen_hmap(fill);
	ft_hmap_alter(fill);
	while (i < fill->map->dim.x - (fill->piece->dim.x - 1))
	{
		while (j < fill->map->dim.y - (fill->piece->dim.y - 1))
		{
			if ((current = ft_get_placement_rating(ft_itovect(i, j), fill)) > best)
			{
				best = current;
				bestplace = ft_itovect(i, j);
			}
			j++;
		}
		j = 0;
		i++;
	}
	temp = ft_ind_to_str(bestplace.x, bestplace.y);
	ft_putstr_fd(temp, 1);
	ft_strdel(&temp);
	return;
}

void		ft_get_info(t_filler *fill)
{
	int		ret;
	int		gotmap;
	int		gotpiece;
	char	*parse;

	ret = 0;
	gotmap = 0;
	gotpiece = 0;
	while ((ret = get_next_line(0, &parse)) > 0)
	{
		if (ft_strstr(parse, "Plateau"))
		{
			ft_get_map(fill->map, parse);
			gotmap = 1;
		}
		else if (ft_strstr(parse, "Piece"))
		{
			ft_get_piece(fill->piece, parse);
			gotpiece = 1;
		}
		if (gotmap && gotpiece)
			break;
	}
}
