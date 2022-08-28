/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/28 22:01:26 by rthammat         ###   ########.fr       */
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
	printf("y %f\n", y);
	printf("y2 %f\n", y2);
	dt->z1 = dt->tab[(int)y][(int)x / (dt->sc_w / 2)]; /////////iso
	dt->z2 = dt->tab[(int)y2][(int)x2 / (dt->sc_w / 2)]; /////////iso
	printf("z1 %f\n", dt->z1);
	printf("z2 %f\n", dt->z2);
	printf("y %f\n", y);
	printf("y2 %f\n", y2);
	dx = x2 - x;
	dy = y2 - y;
	if (dy < 0)
		dy *= -1;
	p = (2 * dy) - dx;
	isomet(&x, &y, dt->z1);
	isomet(&x2, &y2, dt->z2);
	while (x <= x2 || y != y2)
	{
		sleep(1);
		/*printf("x2 %f\n", x2);
		printf("y2 %f\n", x2);
		printf("x %f\n", x);
		printf("y %f\n", y);*/
		mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
		if (x <= x2)
			++x;
		printf("p is %f\n", p);
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
