# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsteyn <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 13:53:08 by gsteyn            #+#    #+#              #
#    Updated: 2018/06/12 14:12:28 by gsteyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = filler
FILES = main.c get_next_line.c
OBJS = $(patsubst %.c,%.o,$(FILES))
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I get_next_line libft
LIBS = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) libs
	gcc -o $(NAME) $(FLAGS) $(OBJS) -L. $(LIBS)

libs:
	make -C ./libft fclean && make -C ./libft

$(OBJS):
	gcc -c $(FLAGS) $(FILES)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
