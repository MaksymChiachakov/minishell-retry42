NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c ft_format_handler.c ft_print_char.c ft_print_str.c \
      ft_print_nbr.c ft_print_hex.c ft_print_ptr.c ft_print_unsigned.c
OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all
