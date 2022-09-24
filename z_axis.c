#include "fdf.h"

void	move(t_fdf *dt, float y2, float s, float mv)
{
	if (dt->z < 0)
		s *= (-1);
	if (dt->z >= 0 && dt->y1 - s <= y2)
		line(dt, dt->x1 + mv, y2);
	else if (dt->z < 0 && dt->y1 - s >= y2)
		line(dt, dt->x1 + mv, y2);
	else
		line(dt, dt->x1 + mv, dt->y1 - s);
	set_start(dt, dt->x1 + (mv * 10), dt->y1 - s);
}

void	z_up(t_fdf *dt, float x2, float y2)
{
	float	s;
	float	x_start;
	float	y_start;

	dt->dx = x2 - dt->x1;
	dt->dy = y2 - dt->y1;
	if (dt->dx < 0)
		dt->dx *= (-1);
	if (dt->dy < 0)
		dt->dy *= (-1);
	s = dt->dy / dt->dx;
	x_start = dt->x1;
	y_start = dt->y1;
	if (dt->x1 < x2)
	{
		while (dt->x1 < x2)
			move(dt, y2, s, 0.1);
	}
	else
	{
		while (dt->x1 > x2)
			move(dt, y2, s, -0.1);
	}
	set_start(dt, x_start, y_start);
}

void	z_down(t_fdf *dt, float x2, float y2)
{
	float	s;
	float	x_start;
	float	y_start;

	dt->dx = x2 - dt->x1;
	dt->dy = y2 - dt->y1;
	if (dt->dx < 0)
		dt->dx *= (-1);
	if (dt->dy < 0)
		dt->dy *= (-1);
	s = dt->dy / dt->dx;
	x_start = dt->x1;
	y_start = dt->y1;
	if (dt->x1 < x2)
	{
		while (dt->x1 < x2)
			move(dt, y2, s, 0.1);
	}
	else
	{
		while (dt->x1 > x2)
			move(dt, y2, s, -0.1);
	}
	set_start(dt, x_start, y_start);
}

void	z_line(t_fdf *dt, float x2, float y2)
{
	if (dt->z < 0)
		z_down(dt, x2, y2);
	else
		z_up(dt, x2, y2);
}

void	z_spot(t_fdf *dt, int h, int w)
{
	int	xsc;

	xsc = dt->xsc;
	if (dt->tab[h + 1][w] != 0)
	{
		dt->z = (dt->tab[h + 1][w]) * (190 / 10) - 10;
		//dt->z = abs((10 - abs(dt->tab[h + 1][w]))) + 190;
		//if (dt->tab[h + 1][w] < 0)
		//	dt->z *= (-1);
		//dt->z -= 10;
		//printf("h + 1 old z %d\n", (dt->tab[h + 1][w] / 10) * 190 - 10);
		//printf("h + 1 z %f\n", dt->z);
		z_line(dt, dt->x1 + xsc, dt->y1 - dt->z);
	}
	if (dt->tab[h][w + 1] != 0)
	{
		dt->z = (dt->tab[h][w + 1]) * (190 / 10) + 10;
		//dt->z = abs((10 - abs(dt->tab[h][w + 1]))) + 190;
		//if (dt->tab[h][w + 1] < 0)
		//	dt->z *= (-1);
		//dt->z += 10;
		z_line(dt, dt->x1 + xsc, dt->y1 - dt->z);
	}
	if (h != 0 && dt->tab[h - 1][w] != 0)
	{
		dt->z = (dt->tab[h - 1][w]) * (190 / 10) + 10;
		//dt->z = abs((10 - abs(dt->tab[h - 1][w]))) + 190;
		//if (dt->tab[h - 1][w] < 0)
		//	dt->z *= (-1);
		//dt->z += 10;
		z_line(dt, dt->x1 - xsc, dt->y1 - dt->z);
	}
	if (w != 0 && dt->tab[h][w - 1] != 0)
	{
		dt->z = (dt->tab[h][w - 1]) * (190 / 10) - 10;
		//dt->z = abs((10 - abs(dt->tab[h][w - 1]))) + 190;
		//if (dt->tab[h][w - 1] < 0)
		//	dt->z *= (-1);
		//dt->z -= 10;
		z_line(dt, dt->x1 - xsc, dt->y1 - dt->z);
	}
}
