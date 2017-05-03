# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouline <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/09 09:36:27 by tbouline          #+#    #+#              #
#    Updated: 2017/04/27 06:03:22 by tbouline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  options.c \
	  error.c \
	  list.c \
	  directories.c \
	  print_rights.c \
	  print_stat.c \
	  display.c \
	  color.c \
	  color2.c \
	  subs.c \
	  tools.c \
	  get_data.c \
	  path.c \
	  sort.c

OBJ = $(SRC:.c=.o)

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

CC = gcc

HEADER = ls.h

OP = -c -I $(HEADER)

all: $(OBJ) $(HEADER)
	make -C libft/
	$(CC) $(FLAGS) $(OP) $(SRC)
	$(CC) -o $(NAME) $(OBJ) libft/libft.a

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
