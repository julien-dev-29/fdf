#include "fdf.h"

void	free_split(char ** split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_map	*init_map(char *filename)
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
	map->width = jr_get_width(filename);
	map->points = malloc(sizeof(t_point) * jr_get_total_points(filename));
	if (!map->points)
		jr_error("Failed to allocate map array");
	k = 0;
	j = 0;
	while (get_next_line(fd, &line) > 0) 
	{
		split = jr_split(line, ' ');
		i = 0;
		while (split[i])
		{
			map->points[k].x = i;
			map->points[k].y = j;
			k++;
			i++;	
		}
		j++;
		free_split(split);
		free(line);
	}
	return map;
}

void	draw_map(t_map *map, char *filename, t_data img)
{
	int	i;
	int	total;

	total = jr_get_total_points(filename);
	i = 0;
	while (i < total)
	{
		jr_mlx_pixel_put(&img, 10 + map->points[i].x * 20,
				10 + map->points[i].y * 20, 0x00FFFFF);
		printf("x: %d, y:  %d\n", map->points[i].x, map->points[i].y);
		i++;
	}
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	*map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1080, 720, "yolo les kikis!");
	img.img = mlx_new_image(mlx, 1080, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	map = init_map("42.fdf");
	draw_map(map, "42.fdf", img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	return (0);
}
