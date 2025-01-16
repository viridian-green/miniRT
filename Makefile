NAME = minirt

SRCS = src/main.c src/parsing.c src/parse_A.c get_next_line/get_next_line.c

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) -L./$(LIBFT) $(OBJS)  -lX11 -lXext -lm -lft -o $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(LIBFT)/libft.a

re: fclean all