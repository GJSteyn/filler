# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 13:53:08 by gsteyn            #+#    #+#              #
#    Updated: 2018/06/12 18:47:56 by gsteyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = filler
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

$(OBJS):
	gcc -c $(INCLUDES) $(FLAGS) $(FILES)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
