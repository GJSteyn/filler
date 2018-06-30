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
	ret->flower = 0;
	return (ret);
}

void		ft_filler(t_filler *fill)
{
	t_2dvect	place;
	char		*temp;

	ft_get_info(fill);
	if (fill->flower == 1 && fill->map->dim.x == 100)
	{
		ft_gen_hmap(fill);
		flower(fill);
		ft_diag_alter(fill);
		ft_print_hmap(fill);
	}
	else
	{
		ft_gen_hmap(fill);
		ft_bubble(fill);
		ft_diag_alter(fill);
	}
	place = ft_optimal_place(fill);
	temp = ft_ind_to_str(place.x, place.y);
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
			ft_get_map(fill, parse);
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

t_2dvect	ft_optimal_place(t_filler *fill)
{
	int		i;
	int		j;
	int		best;
	int		current;
	t_2dvect	bestplace;

	i = -fill->piece->dim.x;
	j = -fill->piece->dim.y;
	best = 0;
	current = 0;
	bestplace = ft_itovect(0, 0);
	while (i < fill->map->dim.x + fill->piece->dim.x)
	{
		while (j < fill->map->dim.y + fill->piece->dim.y)
		{
			if ((current = ft_get_placement_rating(ft_itovect(i, j), fill)) >= best)
			{
				best = current;
				bestplace = ft_itovect(i, j);
			}
			j++;
		}
		j = -fill->piece->dim.y;
		i++;
	}
	return (bestplace);
}
