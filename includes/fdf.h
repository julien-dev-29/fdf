#ifndef FDF_H
# define FDF_H

# include "libjr.h"
# include "get_next_line.h"
# include "jr_split.h"
# include <mlx.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 1080
# define HEIGHT 720

# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define MINUS 27
# define PLUS 24
# define SPACE 49
# define KEY_R 15
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define ESCAPE 53

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_map {
	int		height;
	int		width;
	t_point	*points;
}				t_map;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;	


void	draw_line(t_data *img, int startX, int startY, int endX, 
													int endY, int color);
char    **jr_split(const char *s, char sep);
void	jr_mlx_pixel_put(t_data *data, int x, int y, int color);
void	jr_error(const char *message);
int		jr_get_height(char *filename);
int		jr_get_width(char *filename);
int		jr_get_total_points(char *filename);

#endif
