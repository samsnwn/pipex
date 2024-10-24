NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = pipex.c ft_split.c lib.c lib2.c utils.c errors.c
HEAD = pipex.h
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
 
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
