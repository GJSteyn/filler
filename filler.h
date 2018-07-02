/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:10:40 by gsteyn            #+#    #+#             */
/*   Updated: 2018/07/02 07:37:16 by gsteyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct		s_2dvect
{
	int				x;
	int				y;
}					t_2dvect;

typedef struct		s_player
{
	char			c;
	char			e;
	t_2dvect		c_start;
	t_2dvect		e_start;
}					t_player;

typedef struct		s_map
{
	t_2dvect		dim;
	char			*grid;
	int				size;
	int				init;
}					t_map;

typedef struct		s_piece
{
	t_2dvect		dim;
	char			*grid;
	int				size;
}					t_piece;

typedef struct		s_hmap
{
	int				*grid;
}					t_hmap;

typedef struct		s_filler
{
	t_player		*pl;
	t_map			*map;
	t_piece			*pc;
	t_hmap			*hmap;
}					t_filler;

void				filler(t_filler *filleer);
t_filler			*new_filler(void);
void				get_player_info(t_filler *filler, char *parse);
void				get_info(t_filler *filler);
t_2dvect			optimal_place(t_filler *filler);

t_piece				*init_piece(void);
void				get_piece_dim(t_piece *piece, char *line);
void				get_piece(t_piece *piece, char *parse);

int					itop(int x, int y, t_2dvect dim);
t_2dvect			itovect(int x, int y);
t_2dvect			postovect(int x, t_2dvect dim);
int					valid_pos(t_piece *piece, t_2dvect pos, t_filler *filler);
int					valid_y_axis(t_piece *pc, t_2dvect pos, t_filler *f, int x);
int					piece_fits(t_filler *filler, t_2dvect pos);
int					count_stars(t_filler *filler);
char				*ind_to_str(int x, int y);
int					place_rating(t_2dvect pos, t_filler *filler);
void				get_initial_pos(t_filler *filler);

t_map				*init_map(void);
void				get_map_dim(t_map *map, char *parse);
void				get_map(t_filler *filler, char *parse);
void				print_map(t_filler *filler);

t_hmap				*init_hmap(void);
void				gen_hmap(t_filler *filler);
void				clear_hmap(t_hmap *hmap, int mapsize);
void				get_hval(int x, int y, t_filler *filler);
void				hval_top(int x, int y, t_filler *filler);
void				hval_bot(int x, int y, t_filler *filler);
void				hval_level(int x, int y, t_filler *filler);
void				print_hmap(t_filler *filler);
void				diag_alter(t_filler *filler);
void				bubble(t_filler *filler);
void				bubble_top(t_filler *filler, int i, int x, int y);
void				bubble_bot(t_filler *filler, int i, int x, int y);
void				bubble_level(t_filler *filler, int i, int x, int y);
int					get_target(t_filler *filler);

#endif
