/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/18 08:35:13 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_filler(t_filler *fill)
{
	int		ret;
	char	*parse;

	ret = get_next_line(0, &parse);		// get line with map size
	ft_get_map_dim(fill->map, parse);
	ft_get_map(fill->map);
	ft_get_piece(fill->piece);

}

int		main(void)
{
	int				ret;
	char			*parse;
	t_filler		*fill;

	//ft_putstr_fd("nope\n", 2);
	fill = (t_filler*)malloc(sizeof(t_filler));
	fill->player = (t_player*)malloc(sizeof(t_player));
	fill->map = (t_map*)malloc(sizeof(t_map));
	fill->piece = (t_piece*)malloc(sizeof(t_piece));
	ret = get_next_line(0, &parse);		// get line with player number
	if (parse[10] == '1')
		fill->player->c = 'o';
	else if (parse[10] == '2')
		fill->player->c = 'x';
	//ret = get_next_line(0, &parse);		// get line with map size
	//if (!ret)
	//	ft_putstr_fd("retnope\n", 2);
	//ft_get_map_dim(fill->map, parse);
	//ft_get_map(fill->map);
	//ft_get_piece(fill->piece);
	ft_putstr("19 18\n");
	while (1)
		ft_filler(fill);
	return (0);
}
