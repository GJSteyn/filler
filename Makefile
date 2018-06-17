# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 13:53:08 by gsteyn            #+#    #+#              #
#    Updated: 2018/06/17 14:55:30 by gsteyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gsteyn.filler
FILES = main.c
OBJS = $(patsubst %.c,%.o,$(FILES)) get_next_line.o
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I libft -I get_next_line
LIBS = libft/libft.a
GNL = get_next_line/get_next_line.c

all: $(NAME)

$(NAME): $(OBJS) libs gnl
	gcc -o $(NAME) $(FLAGS) $(OBJS) -L. $(LIBS)

libs:
	make -C ./libft fclean && make -C ./libft

gnl:
	gcc -c $(FLAGS) $(INCLUDES) -o get_next_line.o $(GNL)

fill: rmmain $(OBJS)
	gcc -o $(NAME) $(FLAGS) $(OBJS) -L. $(LIBS)

rmmain:
	rm -rf main.o

$(OBJS):
	gcc -c $(INCLUDES) $(FLAGS) $(FILES)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
