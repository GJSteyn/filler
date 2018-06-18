/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/18 18:55:41 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_filler(t_filler *fill)
{
	int		i;
	int		j;
	int		ret;
	char	*parse;
	char	*temp;

	i = 0;
	j = 0;
	//ft_putstr_fd("Inside filler loop\n", 2);
	if (!(fill->map->dim.x > 0))
	{
		ret = get_next_line(0, &parse);		// get line with map size
		ft_get_map_dim(fill->map, parse);
	}
	else
		ret = get_next_line(0, &parse);
	if (ret == 0)
	{
		ft_putstr_fd("nopegnl\n", 2);
		exit(1);
	}
	/*
	if (ret >0)
	{
		ft_get_map_dim(fill->map, parse);
		ft_putstr_fd("this: ", 2);
		ft_putstr_fd(parse, 2);
	}*/
	ft_get_map(fill->map);
	ft_get_piece(fill->piece);
	//ft_putstr_fd("After trying to get all the parts\n", 2);
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
	//ft_putstr_fd("Before bottom\n", 2);
	temp = ft_ind_to_str(0, 0);
	ft_putstr_fd(temp, 1);
	ft_strdel(&temp);
	/*ft_putstr_fd(parse, 2);
	ft_putchar_fd('\n', 2);*/
}

int		main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	//ft_putstr_fd("nope\n", 2);
	fill = (t_filler*)malloc(sizeof(t_filler));
	if (!fill)
		ft_putstr_fd("fill mallerror\n", 2);
	fill->player = (t_player*)malloc(sizeof(t_player));
	if (!fill->player)
		ft_putstr_fd("player mallerror\n", 2);
	fill->map = (t_map*)malloc(sizeof(t_map));
	if (!fill->map)
		ft_putstr_fd("map mallerror\n", 2);
	fill->piece = (t_piece*)malloc(sizeof(t_piece));
	if (!fill->piece)
		ft_putstr_fd("piece mallerror\n", 2);
	ret = get_next_line(0, &parse);		// get line with player number
	if (ret <= 0)
	{
		ft_putstr_fd("nopegnlmain\n", 2);
		exit(1);
	}
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
