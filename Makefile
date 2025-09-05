NAME = philo
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
CC = cc

SRCS = main.c parsing.c utlis.c routine.c handle_errors.c init.c simulation.c routine_helper.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
