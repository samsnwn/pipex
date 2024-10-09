CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = pipex.c
HEAD = pipex.h
OBJS = $(SRCS:.c=.o)
NAME = pipex
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
