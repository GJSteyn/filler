/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/20 14:10:59 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	*ft_new_filler(void)
{
	t_filler	*ret;

	ft_putstr_fd("Making new filler\n", 2);
	ret = (t_filler*)malloc(sizeof(t_filler));
	if (!ret)
		ft_putstr_fd("fill mallerror\n", 2);
	ret->player = (t_player*)malloc(sizeof(t_player));
	if (!ret->player)
		ft_putstr_fd("player mallerror\n", 2);
	ret->map = (t_map*)malloc(sizeof(t_map));
	if (!ret->map)
		ft_putstr_fd("map mallerror\n", 2);
	ret->piece = (t_piece*)malloc(sizeof(t_piece));
	if (!ret->piece)
		ft_putstr_fd("piece mallerror\n", 2);
	return (ret);
}

void		ft_filler(t_filler *fill)
{
	int		ret;
	int		i;
	int		j;
	int		gotmap;
	int		gotpiece;
	char	*parse;
	char	*temp;

	i = 0;
	j = 0;
	gotmap = 0;
	gotpiece = 0;
	while ((ret = get_next_line(0, &parse)) != 0)
	{
		if (ft_strstr(parse, "Plateau"))
		{
			//ft_putstr_fd("Got plateau\n", 2);
			ft_get_map(fill->map, parse);
			gotmap = 1;
		}
		else if (ft_strstr(parse, "Piece"))
		{
			//ft_putstr_fd("Got piece\n", 2);
			ft_get_piece(fill->piece, parse);
			gotpiece = 1;
		}
		if (gotmap && gotpiece)
			break;
	}
	while (i < fill->map->dim.x - fill->piece->dim.x)
	{
		while (j < fill->map->dim.y - fill->piece->dim.y)
		{
			if (ft_valid_pos(fill->piece, ft_itovect(i, j), fill))
			{
				temp = ft_ind_to_str(i, j);
				ft_putstr_fd(temp, 1);
				//ft_putchar_fd('\n', 2);
				//ft_putstr_fd(temp, 2);
				ft_strdel(&temp);
				return;
			}
			j++;
		}
		j = 0;
		i++;
	}
	temp = ft_ind_to_str(0, 0);
	ft_putstr_fd(temp, 1);
	ft_strdel(&temp);
	exit(1);
}

int			main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	//ft_putstr_fd("nope\n", 2);
	fill = ft_new_filler();
	ret = get_next_line(0, &parse);		// get line with player number
	if (ret <= 0)
	{
		ft_putstr_fd("nopegnlplayer\n", 2);
		exit(1);
	}
	ft_putstr_fd("Getting player number\n", 2);
	if (parse[10] == '1')
		fill->player->c = 'o';
	else if (parse[10] == '2')
		fill->player->c = 'x';
	else
		ft_putstr_fd("player number error\n", 2);
	while (1)
		ft_filler(fill);
	return (0);
}
