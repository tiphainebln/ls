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
	  rights_and_types.c \
	  print_stat.c \
	  display_ls.c \
	  color.c \
	  color2.c \
	  subs.c \
	  determine_types.c \
	  get_data.c \
	  path.c \
	  sort.c \
	  print_total_and_major.c \
	  option_a.c \
	  print_path.c \
	  check_if_hidden.c \
	  subs_tools.c \
	  sort_entries.c \
	  sort_list.c \
	  add_file.c \
	  cmp_list.c \
	  sort_t_entries.c \
	  struct_op.c \
	  store_links.c \
	  get_spaces.c \
	  manage_arguments.c \
	  time_management.c \
	  verification_option.c

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
