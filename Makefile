# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouline <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/09 09:36:27 by tbouline          #+#    #+#              #
#    Updated: 2017/03/09 09:36:29 by tbouline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = ft_ls

SRC = main.c \
	  init.c \
	  options.c \
	  error.c \
	  list.c \
	  directories.c \
	  print_rights.c

CC = gcc

HEADER = ls.h

OBJ = main.o \
	  init.o \
	  options.o \
	  error.o \
	  list.c \
	  directories.o \
	  print_rights.o

FLAG = -Wall -Wextra -Werror

OP = -c -I $(HEADER)

all: $(EXEC)

$(EXEC): $(OBJ) $(HEADER)
	make -C libft/
	$(CC) $(FLAG) $(OP) $(SRC)
	$(CC) -o $(EXEC) $(OBJ) -L libft/ -lft

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re