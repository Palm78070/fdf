/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:37:13 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/15 02:44:30 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	choose_line(t_fdf *dt, float x2, float y2)
{
	if (!slope1(dt, x2, y2))
		z_line(dt, x2, y2);
	else
		line(dt, x2, y2 );
}

void	check_draw(t_fdf *dt, int h, int w)
{
	float	y2;

	dt->z = dt->tab[h][w].z * dt->zm;
	dt->c = dt->tab[h][w].color;
	if (w + 1 <= dt->width - 1)
		dt->zx = dt->tab[h][w + 1].z * dt->zm;
	if (h + 1 <= dt->height - 1)
		dt->zy = dt->tab[h + 1][w].z * dt->zm;
	y2 = dt->y1;
	//////// h w ////////////////////////////
	set_start(dt, dt->x1, dt->y1 - dt->z);
	/////// h w+1 ///////////////////////////
	if ((w < dt->width - 1) \
		&& !slope1(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx))
		z_line(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx);
	else if (w < dt->width - 1)
		line(dt, dt->x1 + dt->xsc, y2 - dt->ysc - dt->zx);
	/////// h+1 w ///////////////////////////
	if ((h < dt->height - 1) \
		&& !slope1(dt, dt->x1 + dt->xsc, y2 + dt->ysc - dt->zy))
		z_line(dt, dt->x1 + dt->xsc, y2 + dt->ysc - dt->zy);
	else if (h < dt->height - 1)
		line(dt, dt->x1 + dt->xsc, y2 + dt->ysc - dt->zy);
	set_start(dt, dt->x1 + dt->xsc, dt->y1 + dt->z - dt->ysc);
}

void	draw4(t_fdf *dt)
{
	int	w;
	int	h;
	float	x2;
	float	y2;

	h = -1;
	x2 = (dt->sc_w / 5);
	y2 = dt->sc_h / 2 + 100;
	set_start(dt, dt->sc_w / 5, dt->sc_h / 2 + 100);
	while (++h < dt->height)
	{
		w = -1;
		while (++w < dt->width)
			check_draw(dt, h, w);
		y2 += dt->ysc;
		x2 += dt->xsc;
		set_start(dt, x2, y2);
	}
}
