NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = main.c first_child.c second_child.c ft_split.c lib.c lib2.c utils.c errors.c
HEAD = pipex.h
OBJS = $(SRCS:.c=.o)

OUTFILE = outfile.txt

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
 
fclean: clean
	$(RM) $(NAME) $(OUTFILE)

re: fclean all

.PHONY: all clean fclean re
