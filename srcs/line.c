#include "fdf.h"

void	draw_line(t_data *img, int x0, int y0, int x1, 
		int y1, int color)
{
	int	dx;
	int	dy;
	int	pixelX;
	int pixelY;
	int	p0;

	dx = x1 - x0;
	dy = y1 - y0;
	p0 = 2 * dy - dx;
	jr_mlx_put_pixel(img, x0, y0, 0x00FFF);

	while (x0 <= x1)
	{
		x0++;
		if (p0 < 0)
		{
			px
		}
	}
}

void	draw_circle(t_data *img, int x, int y, int radius)
{
	
}
