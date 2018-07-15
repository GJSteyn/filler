# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 13:53:08 by gsteyn            #+#    #+#              #
#    Updated: 2018/07/15 14:22:10 by gsteyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gsteyn.filler
FILES = map.c piece.c logic.c main.c heatmap.c filler.c vects.c bubble.c \
		hval.c vert_alter.c
OBJS = $(patsubst %.c, bin/%.o, $(FILES)) ./bin/get_next_line.o
SRCS = $(patsubst %.c, srcs/%.c, $(FILES))
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I libft -I get_next_line -I.
LIBS = libft/libft.a
GNL = get_next_line/get_next_line.c

all: $(NAME)

$(NAME): $(OBJS) libs gnl
	gcc -o $(NAME) $(FLAGS) $(OBJS) -L. $(LIBS)

libs:
	make -C ./libft fclean && make -C ./libft

gnl:
	gcc -c $(FLAGS) $(INCLUDES) -o ./bin/get_next_line.o $(GNL)

$(OBJS):
	gcc -c $(INCLUDES) $(FLAGS) $(SRCS)
	mv *.o ./bin

fill: rmmain $(OBJS)
	gcc -o $(NAME) $(FLAGS) $(OBJS) -L. $(LIBS)

rmmain:
	rm -rf ./bin/main.o

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
