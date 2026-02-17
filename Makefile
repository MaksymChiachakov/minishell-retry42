# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/29 14:15:23 by mchiacha          #+#    #+#              #
#    Updated: 2026/02/13 17:28:08 by fmoses           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -ILibft -g

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = srcs
SRC = $(shell find ./srcs -name "*.c") \
	$(shell find ./libft -name "*.c") \
	$(shell find ./ft_printf -name "*.c") \
	$(shell find ./get_next_line -name "*.c")

OBJ = $(SRC:.c=.o)

LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
 