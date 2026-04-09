#include "fdf.h"

static void  jr_get_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;
	int		i;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		jr_error("Failed to open file");
	while ((i = get_next_line(fd, &line)) != 0)
	{
		if (i == -1)
		{
			free(line);
			jr_error("Failed to parse file");
		}
		printf("%s\n", line);
		height++;
		printf("%d\n", height);
	}
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1080, 720, "yolo les kikis!");
	img.img = mlx_new_image(mlx, 1080, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	draw_line(&img, 0, 0, WIDTH, HEIGHT, 0xFFFFFF);
	draw_line(&img, 0, 720, 1080, 0, 0xFFFFFF);

	jr_get_height("42.fdf");

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
