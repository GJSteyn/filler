/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:04:02 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/01 14:20:11 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_map	*ft_init_map(void)
{
	t_map	*ret;

	ret = (t_map*)malloc(sizeof(t_map));
	ret->dim = ft_itovect(0, 0);
	ret->grid = NULL;
	ret->size = 0;
	ret->init = 0;
	return (ret);
}

void	ft_get_map_dim(t_map *map, char *parse)
{
	char	*start;

	start = parse + 8;
	while (ft_isdigit(*start))
		map->dim.x = (map->dim.x * 10) + (*start++ - '0');
	start++;
	while (ft_isdigit(*start))
		map->dim.y = (map->dim.y * 10) + (*start++ - '0');
	map->size = map->dim.x * map->dim.y;
}

void	ft_get_map(t_filler *f, char *parse)
{
	int		i;
	int		read;
	char	*line;
	t_map	*map;

	map = f->map;
	if (!map->init)
		ft_get_map_dim(map, parse);
	i = 0;
	if (map->grid == NULL)
		map->grid = ft_strnew(map->size + 1);
	read = get_next_line(0, &line);
	ft_strclr(map->grid);
	while (i < map->dim.x)
	{
		read = get_next_line(0, &line);
		if (!read)
			ft_putstr_fd("mapnope\n", 2);
		ft_strcat(map->grid, line + 4);
		i++;
	}
	if (map->init == 0)
		ft_get_initial_pos(f);
	map->init = 1;
}

void	ft_print_map(t_filler *f)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < f->map->dim.x)
	{
		ft_putnstr_fd(&(f->map->grid[j]), 2, f->map->dim.y);
		ft_putchar_fd('\n', 2);
		i++;
		j += f->map->dim.y;
	}
}
