/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_axis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:53:29 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/14 11:54:02 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move(t_fdf *dt, float y2, float s, float mv)
{
	if (dt->y1 < y2)
		s *= (-1);
	if (s > 0 && dt->y1 - s <= y2)
		line(dt, dt->x1 + mv, y2);
	else if (s < 0 && dt->y1 - s >= y2)
		line(dt, dt->x1 + mv, y2);
	else
		line(dt, dt->x1 + mv, dt->y1 - s);
	set_xy1(dt, dt->x1 + (mv * 10), dt->y1 - s);
}

static void	z_up(t_fdf *dt, float x2, float y2)
{
	float	s;
	float	x_start;
	float	y_start;

	dt->dx = fabsf(x2 - dt->x1);
	dt->dy = fabsf(y2 - dt->y1);
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
	set_xy1(dt, x_start, y_start);
}

static void	z_down(t_fdf *dt, float x2, float y2)
{
	float	s;
	float	x_start;
	float	y_start;

	dt->dx = fabsf(x2 - dt->x1);
	dt->dy = fabsf(y2 - dt->y1);
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
	set_xy1(dt, x_start, y_start);
}

void	z_line(t_fdf *dt, float x2, float y2)
{
	if (dt->y1 < y2)
		z_down(dt, x2, y2);
	else
		z_up(dt, x2, y2);
}
