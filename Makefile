NAME = minirt

SRCS = main.c get_next_line/get_next_line.c
OBJS = $(SRCS:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -L/usr/lib/X11 -lXext -lX11 -lm
MLX_PATH = minilibx-linux
MLX = minilibx-linux/libmlx.a

all: $(NAME) $(MLX)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_PATH)
	$(CC) $(CFLAGS) -L$(MLX_PATH) $(OBJS) -lmlx_Linux -lX11 -lXext -lm -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME) $(MLX)
	rm -f $(NAME)

re: fclean all