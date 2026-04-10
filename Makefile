NAME = fdf

SRC = fdf.c srcs/*.c

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
