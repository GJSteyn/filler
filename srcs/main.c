/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/25 17:26:37 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		ft_get_initial_pos(t_filler *fill)
{
	int			i;
	int			map_size;

	i = 0;
	map_size = fill->map->dim.x * fill->map->dim.y;
	while (i < map_size)
	{
		if (fill->map->grid[i] == fill->player->c - 32)
			fill->player->c_start = ft_postovect(i, fill->map->dim);
		else if (fill->map->grid[i] == fill->player->e - 32)
			fill->player->e_start = ft_postovect(i, fill->map->dim);
		i++;
	}
}

void		ft_filler(t_filler *fill)
{
	int		ret;
	int		i;
	int		j;
	int		gotmap;
	int		gotpiece;
	int		best;
	int		current;
	t_2dvect	bestplace;
	char	*parse;
	char	*temp;

	i = 0;
	j = 0;
	best = 0;
	current = 0;
	bestplace = ft_itovect(0, 0);
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

int			main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	fill = ft_new_filler();
	ret = get_next_line(0, &parse);		// get line with player number
	if (ret <= 0)
	{
		ft_putstr_fd("nopegnlplayer\n", 2);
		exit(1);
	}
	ft_putstr_fd("After first gnl\n", 2);
	if (parse[10] == '1')
	{
		fill->player->c = 'o';
		fill->player->e = 'x';
	}
	else if (parse[10] == '2')
	{
		fill->player->c = 'x';
		fill->player->e = 'o';
	}
	else
		ft_putstr_fd("player number error\n", 2);
	while (1)
		ft_filler(fill);
	return (0);
}
