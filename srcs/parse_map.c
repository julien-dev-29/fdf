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
    int     fd;
    char    *line;
    char    **split;
    int     width;
    int     current_width;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        jr_error("Failed to open file");

    if (get_next_line(fd, &line) <= 0)
        jr_error("Empty file");

    split = jr_split(line, ' ');
    if (!split)
        jr_error("Split failed");

    width = 0;
    while (split[width])
        width++;
    free(line);
    while (get_next_line(fd, &line) > 0)
    {
        split = jr_split(line, ' ');
        if (!split)
            jr_error("Split failed");

        current_width = 0;
        while (split[current_width])
            current_width++;

        if (current_width != width)
        {
            free(line);
            close(fd);
            jr_error("Map is not rectangular");
        }
        free(line);
    }
    close(fd);
    return (width);
}

int	jr_get_total_points(char *filename)
{
	return (jr_get_height(filename) * jr_get_width(filename));
}
