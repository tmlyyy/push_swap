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
			  disorder.c

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

TEST_SRC	= dev_test_operations.c \
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
			  disorder.c

.PHONY: all clean fclean re test_ops