/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:10:40 by gsteyn            #+#    #+#             */
/*   Updated: 2018/06/25 09:48:02 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <string.h>

typedef struct		s_player
{
	char			c;
	char			e;
}					t_player;

typedef struct		s_2dvect
{
	int				x;
	int				y;
}					t_2dvect;

typedef struct		s_map
{
	t_2dvect		dim;
	char			*grid;
}					t_map;

typedef struct		s_piece
{
	t_2dvect		dim;
	char			*grid;
}					t_piece;

typedef struct		s_hmap
{
	int				*grid;
}					t_hmap;

typedef struct		s_filler
{
	t_player		*player;
	t_map			*map;
	t_piece			*piece;
	t_hmap			*hmap;
}					t_filler;

void				ft_filler(t_filler *fill);
t_filler			*ft_new_filler(void);

t_piece				*ft_init_piece(void);
void				ft_get_piece_dim(t_piece *piece, char *line);
void				ft_get_piece(t_piece *piece, char *parse);

int					ft_itop(int x, int y, t_2dvect dim);
t_2dvect			ft_itovect(int x, int y);
int					ft_valid_pos(t_piece *piece, t_2dvect pos, t_filler *fill);
char				*ft_ind_to_str(int x, int y);
int					ft_get_placement_rating(t_2dvect pos, t_filler *filler);

t_map				*ft_init_map(void);
void				ft_get_map_dim(t_map *map, char *parse);
void				ft_get_map(t_map *map, char *parse);
void				ft_print_map(t_filler *filler);

t_hmap				*ft_init_hmap(void);
void				ft_gen_hmap(t_filler *filler);
void				ft_clear_hmap(t_hmap *hmap, int mapsize);
void				ft_get_hval(int x, int y, t_filler *filler);
void				ft_print_hmap(t_filler *filler);
void				ft_hmap_alter(t_filler *filler);
int					ft_get_divnum(int i);
void				ft_row_alter(int row, t_filler *filler);
void				ft_col_alter(int col, t_filler *filler);

#endif
