#include "fdf.h"

static void	check_first_row(t_fdf *dt, int h, int w)
{
	float	y_start;

	dt->z = dt->tab[h][w].z * dt->zm;
	if (w + 1 <= dt->width - 1)
		dt->zx = dt->tab[h][w + 1].z * dt->zm;
	if (h + 1 <= dt->height - 1)
		dt->zy = dt->tab[h + 1][w].z * dt->zm;
	y_start = dt->y1;
	set_xy1(dt, dt->x1 + dt->xsc, dt->y1 + dt->z - dt->ysc);
}

int	find_x_edge(t_fdf *dt)
{
	int	w;
	int	h;
	float	x0;
	float	y0;

	h = 0;
	w = -1;
	x0 = dt->x_start;
	y0 = dt->y_start;
	set_xy1(dt, x0, y0);
	set_projection(dt);
	while (++w < dt->width)
		check_first_row(dt, h, w);
	set_xy1(dt, dt->x1 - dt->xsc + dt->xsc, dt->y1 + dt->ysc + dt->ysc);
	h = -1;
	while (++h < dt->height)
		set_xy1(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
	return (dt->x1);
}

void	mv_middle(t_fdf *dt, float x_last)
{
	printf("x_start in md before %f\n", dt->x_start);
	printf("x_last %f\n", x_last);
	float	img_gap;

	img_gap = x_last - dt->x_start;
	printf("img_gap %f\n", img_gap);
	dt->x_start = (dt->sc_w / 2) - (img_gap / 2);
	printf("x_start in md %f\n", dt->x_start);
}
