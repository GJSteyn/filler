/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:04:02 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/18 13:57:03 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_get_map_dim(t_map *map, char *parse)
{
	char	*start;

	map->dim.x = 0;
	map->dim.y = 0;
	start = parse + 8;
	while (ft_isdigit(*start))
		map->dim.x = (map->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		map->dim.y = (map->dim.y * 10) + (*start++ - '0');
}

void	ft_get_map(t_map *map)
{
	int		i;
	int		read;
	char	*line;

	i = 0;
	if (!map->grid)
		map->grid = (char*)ft_memalloc(map->dim.x * map->dim.y);
	read = get_next_line(0, &line);		// skip the line with column indices
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
