
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS =	philo.c \
		utils.c  \
		actions.c \
		monitor.c  \

OBJS = $(SRCS:.c=.o)

all:$(NAME)

$(NAME):$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all