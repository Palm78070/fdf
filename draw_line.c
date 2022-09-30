/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/09/28 17:44:59 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	xy_init(t_fdf *dt, float *x, float *y)
{
	*x = dt->x1;
	*y = dt->y1;
}

void	x_inc(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	p;

	xy_init(dt, &x, &y);
	dt->dx = fabs(x2 - x);
	dt->dy = fabs(y2 - y);
	//if (dt->dy < 0)
	//	dt->dy *= -1;
	//printf("dy %f\n", dt->dy);
	//printf("dx %f\n", dt->dx);
	p = (2 * dt->dy) - dt->dx;
	while (x <= x2 || y != y2)
	{
		mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
		if (x <= x2)
			++x;
		if (p < 0)
			p = p + (2 * dt->dy);
		else
		{
			p = p + (2 * dt->dy) - (2 * dt->dx);
			if (dt->y1 <= y2)
			{
				if (y++ >= y2 && x > x2)
					break ;
			}
			else if (y-- <= y2 && x > x2)
				break ;
		}
	}
}

/*void	x_inc(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	p;

	xy_init(dt, &x, &y);
	dt->dx = x2 - x;
	dt->dy = y2 - y;
	p = 2 * dt->dy - dt->dx;
	while (x < x2)
	{
		if (p >= 0)
		{
			mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
			++y;
			p = p + 2 * dt->dy - 2 * dt->dx;
		}
		else
		{
			mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
			p = p + 2 * dt->dy;
			x += 1;
		}
	}
}*/

void	x_dec(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	p;

	xy_init(dt, &x, &y);
	dt->dx = x - x2;
	dt->dy = y - y2;
	if (dt->dy < 0)
		dt->dy *= -1;
	p = (2 * dt->dy) - dt->dx;
	while (x >= x2 || y != y2)
	{
		mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
		if (x >= x2)
			--x;
		if (p < 0)
			p = p + (2 * dt->dy);
		else
		{
			p = p + (2 * dt->dy) - (2 * dt->dx);
			if (dt->y1 <= y2)
			{
				if (y++ >= y2 && x < x2)
					break ;
			}
			else if (y-- <= y2 && x < x2)
				break ;
		}
	}
}

void	line(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;

	xy_init(dt, &x, &y);
	if (dt->x1 < x2)
		x_inc(dt, x2, y2);
	else
		x_dec(dt, x2, y2);
}
