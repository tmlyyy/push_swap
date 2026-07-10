NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC			= main.c \
			  error_handling.c \
			  string_validation.c \
			  utils.c \
			  argument_parser.c \
			  stack_creation.c \
			  node_helpers.c \
			  operations_swap.c \
			  operations_push.c \
			  operations_rotate.c \
			  operations_reverse_rotate.c \
			  disorder.c \
			  assign_indexes.c \
			  algorithm_utils.c \
			  algorithm_simple.c \
			  algorithm_medium.c \
			  algorithm_complex.c \
			  algorithm_complex_utils.c \
			  bench.c \
			  bench_utils.c \
			  parsing_utils.c\
			  split_validations.c

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