/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:04:02 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/22 16:11:20 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_get_map_dim(t_map *map, char *parse)
{
	char	*start;

	map->dim.x = 0;
	map->dim.y = 0;
	start = parse + 8;
	//ft_putstr_fd("Getting map dimension\n", 2);
	while (ft_isdigit(*start))
		map->dim.x = (map->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		map->dim.y = (map->dim.y * 10) + (*start++ - '0');
}

void	ft_get_map(t_map *map, char *parse)
{
	int		i;
	int		read;
	char	*line;

	ft_get_map_dim(map, parse);
	i = 0;
	if (!map->grid)
		map->grid = (char*)ft_memalloc(map->dim.x * map->dim.y + 1);
	read = get_next_line(0, &line);		// skip the line with column indices
	//ft_putstr_fd("Getting the map\n", 2);
	ft_strclr(map->grid);
	while (i < map->dim.x)
	{
		read = get_next_line(0, &line);
		if (!read)
			ft_putstr_fd("mapnope\n", 2);
		ft_strcat(map->grid, line + 4);
		i++;
	}
}

void	ft_print_map(t_filler *fill)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < fill->map->dim.x)
	{
		ft_putnstr_fd(&(fill->map->grid[j]), 2, fill->map->dim.y);
		ft_putchar_fd('\n', 2);
		i++;
		j += fill->map->dim.y;
	}
}
