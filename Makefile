# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouline <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/09 09:36:27 by tbouline          #+#    #+#              #
#    Updated: 2017/05/25 04:31:50 by tbouline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  options.c \
	  error.c \
	  add_list.c \
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
	  sort.c \
	  print.c \
	  option_a.c \
	  storage.c \
	  print_path.c \
	  check_if_hidden.c \
	  subs_tools.c \
	  sort_entries.c \
	  sort_list.c \
	  add_file.c \
	  cmp_list.c \

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
