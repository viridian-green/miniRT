NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -Iheaders -Iinclude -Isrc -O3 -Wunreachable-code -Ofast

# Paths
OBJ_DIR = objects/
SRC_DIR = src/
#CREATE PATHS TO FOLDERS INSIDE OF SRC (IF NEEDED)
HEADERS_DIR = headers/
LIBFT_DIR = libs/libft/
GNL_DIR = libs/get_next_line/
LIBMLX = libs/MLX42/

LIBS = $(LIBMLX)/build/libmlx42.a -ldl -L/opt/homebrew/lib -lglfw -pthread -lm #-L/opt/homebrew/lib for mac
LIBS += $(LIBFT_DIR)/libft.a $(GNL_DIR)/libgnl.a

INCLUDES = -I$(HEADERS_DIR) -I$(LIBMLX)/include -I$(LIBFT_DIR)

SRCS = 	src/main.c \
		src/parsing.c \
		src/parse_ambience.c \
		src/parse_camera.c \
		src/parse_light.c \
		src/parse_objects.c \
		src/utils.c \
		src/math.c \
		src/checks.c \
		src/init.c \
		src/lights.c \
		src/shadow.c \
		src/init_objects.c \
		src/error_handling.c \
		src/viewport.c \
		src/color.c \
		src/ray.c

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HDRS = $(addprefix $(HEADERS_DIR), minirt.h structures.h)

LIBFT 			= $(LIBFT_DIR)/libft.a
LIBFT_LIB 		= -Llibft -lft

all: libmlx $(LIBFT) $(GNL_DIR)/libgnl.a $(NAME)

libmlx:
	@if [ ! -d "libs/MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git libs/MLX42; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@make --quiet -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) --quiet -C $(LIBFT_DIR) all

$(GNL_DIR)/libgnl.a:
	@$(MAKE) -C $(GNL_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(HDRS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[32;1mminiRT is ready\033[5m ✓ ✓ ✓\033[0m"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C ${GNL_DIR} clean
	@echo "\033[37;1mObject files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(MAKE) --no-print-directory -C ${GNL_DIR} fclean
	@rm -rf $(LIBMLX)/build
	@echo "\033[37;1mExecutable removed.\033[0m"

re: fclean all

norminette:
	norminette ${SRC_DIR} ${HEADERS_DIR} ${LIBFT_DIR} ${GNL_DIR}

.PHONY: all clean fclean re libmlx $(LIBFT)
