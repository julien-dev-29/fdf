#include "fdf.h"

int	jr_get_height(char *filename)
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
		height++;
		free(line);
	}
	if (close(fd) == -1)
		jr_error("close error");
	return (height);
}

int jr_get_width(char *filename)
{
	int		width;
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		jr_error("Failed to open file");
	i = get_next_line(fd, &line);	
	if (i != -1)
		split = jr_split(line, ' ');
	width = 0;
	j = 0;
	while (split[j++] != NULL)
		width++;
	return (width);
}
