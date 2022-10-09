/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:37:13 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/09 23:45:17 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	check_draw(t_fdf *dt, int h, int w)
{
	if (dt->tab[h][w] != 0)
	{
		dt->z = dt->zm * dt->tab[h][w];
		if (w - 1 >= 0 && dt->tab[h][w - 1] != 0)
			set_start(dt, dt->x1, dt->y1 - (dt->zm * dt->tab[h][w - 1]));
		else
			set_start(dt, dt->x1, dt->y1 - dt->z);
		if (dt->tab[h][w + 1] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		if (dt->tab[h + 1][w] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		set_start(dt, dt->x1, dt->y1 + dt->z);
	}
	if (dt->tab[h][w] == 0)
	{
		if (dt->tab[h + 1][w] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		if (dt->tab[h][w + 1] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		z_spot(dt, h, w);
	}
	set_start(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
	if (w == dt->width - 2)
	{
		printf("w %i\n", w);
		//line(dt, dt->x1, dt->y1 - 300); /////////close
		line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc); /////////close
	}
}*/

/*void	check_draw(t_fdf *dt, int h, int w)
{
	float	z0;
	//if (dt->tab[h][w] != 0)
	//{
		if (w == 0)
			z0 = dt->tab[h][w];
		dt->z = (abs(abs(dt->tab[h][w]) - fabsf(z0))) * 190;
		if (dt->tab[h][w] < 0)
			dt->z *= (-1);
		printf("z %f\n", dt->z);
		set_start(dt, dt->x1, dt->y1 - dt->z);
		//if (dt->tab[h][w + 1] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		//if (dt->tab[h + 1][w] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		set_start(dt, dt->x1, dt->y1 + dt->z);
	//}
	if (dt->tab[h][w] == 0)
	{
		if (dt->tab[h + 1][w] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		if (dt->tab[h][w + 1] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		z_spot(dt, h, w);
	}
	set_start(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
}*/

int	slope1(t_fdf *dt, float x2, float y2)
{
	float	s;

	dt->dx = fabs(x2 - dt->x1);
	dt->dy = fabs(y2 - dt->y1);
	s = dt->dy / dt->dx;
	if (roundf(s) >= 0 && roundf(s) <= 1)
		return (1);
	return (0);
}

/*void	check_draw(t_fdf *dt, int h, int w)
{
	float	x2;
	float	y2;

	dt->z = dt->tab[h][w] * dt->zm;
	if (w + 1 <= dt->width - 1)
		dt->zx = dt->tab[h][w + 1] * dt->zm;
	if (h + 1 <= dt->height - 1)
		dt->zy = dt->tab[h + 1][w] * dt->zm;
	//////// h w ////////////////////////////
	set_start(dt, dt->x1, dt->y1 - dt->z);
	/////// h w+1 ///////////////////////////
	if (!slope1(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc - dt->zx))
		z_line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc - dt->zx);
	else
		line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc - dt->zx);
	/////// h+1 w ///////////////////////////
	if (!slope1(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc - dt->zy))
		z_line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc - dt->zy);
	else
		line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc - dt->zy);
	set_start(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc - dt->zx);
}*/

/*void	close_w(t_fdf *dt)
{
	float	y2;

	set_start(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
	y2 = dt->y1;
	set_start(dt, dt->x1, dt->y1 - dt->z);
	/////////////////////////////////
	//printf("x %f y %f\n", dt->x1 + dt->xsc, dt->y1);
	/////////////////////////////////
	if (!slope1(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx))
		z_line(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx);
	else
		line(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx);
	set_start(dt, dt->x1, dt->y1 + dt->z);
	set_start(dt, dt->x1 - dt->xsc, dt->y1 - dt->ysc);
}

void	close_h(t_fdf *dt, float y2)
{
	float	offset;
	float	end_point;
	
	offset = fabs(y2 - dt->ysc - dt->zx - dt->y1);
	end_point = y2 + dt->ysc - dt->zy;
	set_start(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx);
	if (!slope1(dt, dt->x1 + dt->xsc, end_point - offset))
		z_line(dt, dt->x1 + dt->xsc, end_point - offset);
	else
		line(dt, dt->x1 + dt->xsc, end_point - offset);
	set_start(dt, dt->x1 - dt->xsc, y2 + dt->ysc + dt->zx);
}*/

void	check_draw(t_fdf *dt, int h, int w)
{
	float	y2;

	dt->z = dt->tab[h][w] * dt->zm;
	dt->c = dt->color[h][w];
	if (w + 1 <= dt->width - 1)
		dt->zx = dt->tab[h][w + 1] * dt->zm;
	if (h + 1 <= dt->height - 1)
		dt->zy = dt->tab[h + 1][w] * dt->zm;
	y2 = dt->y1;
	//if (h == dt->height - 2)
	//	close_w(dt);
	//////// h w ////////////////////////////
	set_start(dt, dt->x1, dt->y1 - dt->z);
	/////// h w+1 ///////////////////////////
	if ((w < dt->width - 1) && !slope1(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx))
		z_line(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx);
	else if (w < dt->width - 1)
		line(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx);
	/////// h+1 w ///////////////////////////
	if ((h < dt->height - 1) && !slope1(dt, dt->x1 + dt->xsc, y2 + dt->ysc - dt->zy))
		z_line(dt, dt->x1 + dt->xsc, y2 + dt->ysc - dt->zy);
	else if (h < dt->height - 1)
		line(dt, dt->x1 + dt->xsc, y2 + dt->ysc - dt->zy);
	//if (w == dt->width - 2)
	//	close_h(dt, y2);
	set_start(dt, dt->x1 + dt->xsc, dt->y1 + dt->z - dt->ysc);
}

/*static void	check_x(t_fdf *dt, int w, int h, float x2)
{
	while (++h < dt->height - 1)
		x2 += dt->xsc;
	while (++w < dt->width - 1)
		x2 += dt->xsc;
}

static void	check_y(t_fdf *dt, float y2)
{
	int	h;

	h = -1;
	while (++h < dt->height - 1)
		y2 = y2 - dt->tab[h][0] + dt->ysc;
}*/

void	draw4(t_fdf *dt)
{
	int	w;
	int	h;
	float	x2;
	float	y2;

	h = -1;
	x2 = (dt->sc_w / 5);
	y2 = dt->sc_h / 2 + 100;
	////////////////////////
	//check_x(dt, -1, -1, x2);
	//check_y(dt, y2);
	////////////////////////
	set_start(dt, dt->sc_w / 5, dt->sc_h / 2 + 100);
	//while (++h < dt->height - 1)
	while (++h < dt->height)
	{
		w = -1;
		//while (++w < dt->width - 1)
		while (++w < dt->width)
			check_draw(dt, h, w);
		y2 += dt->ysc;
		x2 += dt->xsc;
		set_start(dt, x2, y2);
	}
}
