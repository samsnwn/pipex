CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = pipex.c
HEAD = pipex.h
OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(NAME)

# create object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# create executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
 
fclean: clean
	$(RM) $(NAME) outfile.txt

re: fclean all

.PHONY: all clean fclean re
