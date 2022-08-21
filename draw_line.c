/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/21 22:49:04 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*float	d_init(t_fdf *dt, float x2, float y2)
{
	float	res;

	if (c == 'x')
		res = x2 - dt->x1;
	else
		res = y2 - dt->y1;
}*/

static void	xy_init(t_fdf *dt, float *x, float *y)
{
	*x = dt->x1;
	*y = dt->y1;
}

void	x_inc(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	p;

	xy_init(dt, &x, &y);
	dx = x2 - x;
	dy = y2 - y;
	if (dy < 0)
		dy *= -1;
	p = (2 * dy) - dx;
	while (x <= x2 || y != y2)
	{
		mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
		if (x <= x2)
			++x;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - (2 * dx);
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

void	x_dec(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	p;

	xy_init(dt, &x, &y);
	dx = x - x2;
	dy = y - y2;
	if (dy < 0)
		dy *= -1;
	p = (2 * dy) - dx;
	while (x >= x2 || y != y2)
	{
		mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
		if (x >= x2)
			--x;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - (2 * dx);
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
	if (dt->x1 < x2)
		x_inc(dt, x2, y2);
	else
		x_dec(dt, x2, y2);
}
