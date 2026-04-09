NAME = fdf

SRC = fdf.c srcs/line.c srcs/utils.c  srcs/get_next_line.c srcs/jr_split.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = mlx
MLX_FLAGS = -L$(MLX_DIR) -Llibjr -lmlx -lXext -lX11 -lm -lbsd -ljr

INCLUDES = -I$(MLX_DIR) -Iincludes -Ilibjr

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all
