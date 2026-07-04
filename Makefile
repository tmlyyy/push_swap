NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC			= main.c \
			  error_handling.c \
			  string_validation.c \
			  utils.c \
			  argument_parser.c \
			  stack_creation.c
 
OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re