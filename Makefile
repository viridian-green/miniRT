NAME = minirt

SRCS = src/main.c src/parsing.c get_next_line/get_next_line.c

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -L/usr/lib/X11 -lXext -lX11 -lm
MLX_PATH = minilibx-linux
LIBFT = libft
MLX = minilibx-linux/libmlx.a

all: $(NAME) $(MLX)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(MAKE) -C $(MLX_PATH)
	$(CC) $(CFLAGS) -L$(MLX_PATH) -L./$(LIBFT) $(OBJS) -lmlx_Linux -lX11 -lXext -lm -lft -o $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(MLX_PATH)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(MLX)
	rm -f $(LIBFT)/libft.a

re: fclean all