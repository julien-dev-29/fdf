#include "fdf.h"

void init_map(char *filename)
{
	t_map	*map;
	char	*line;
	char	**split;
	int		fd;
	int		i;
	int		j;
	int		k;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		jr_error("Failed to open file");
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		jr_error("Failed to init map");
	map->height = jr_get_height(filename);
	map->width = jr_get_width(filename);;
	map->array = malloc(sizeof(int **) * map->height);
	if (!map->array)
		jr_error("Failed to allocate map array");
	i = 0;
	j = 0;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		split = jr_split(line, ' ');
		map->array[i] = malloc(sizeof(int) * map->width);
		if (!map->array[i])
			jr_error("malloc failed");
		while (split[j])
		{
			map->array[i][j] = jr_atoi(split[j]);	
			j++;
		}
		free(line);
		i++;
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

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
