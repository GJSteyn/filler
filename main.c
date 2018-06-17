/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:24:16 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/17 15:29:15 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_get_map_dim(t_map *map, char *parse)
{
	int		i;
	char	*start;

	map->dim.x = 0;
	map->dim.y = 0;
	i = 0;
	start = parse + 8;
	while (ft_isdigit(*start))
		map->dim.x = (map->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		map->dim.y = (map->dim.y * 10) + (*start++ - '0');
}


int	main(void)
{
	int				ret;
	char			*parse;
	t_player		*player;
	t_map			*map;

	ft_putstr_fd("nope\n", 2);
	player = (t_player*)malloc(sizeof(t_player));
	map = (t_map*)malloc(sizeof(t_map));
	ret = get_next_line(0, &parse);		// get line with player number
	if (parse[10] == '1')
		player->c = 'o';
	else if (parse[10] == '2')
		player->c = 'x';
	ret = get_next_line(0, &parse);		// get line with map size
	ft_get_map_dim(map, parse);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("Player number: ", 2);
	ft_putchar_fd(player->c, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("Map dim x: ", 2);
	ft_putnbr_fd(map->dim.x, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("Map dim y: ", 2);
	ft_putnbr_fd(map->dim.y, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr("19 18\n");
	
	return (0);
}
