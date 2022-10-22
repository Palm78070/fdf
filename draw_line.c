/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/22 16:47:21 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	xy_init(t_fdf *dt, float *x, float *y, float *p)
{
	*x = dt->x1;
	*y = dt->y1;
	*p = (2 * dt->dy) - dt->dx;
}

static int	check_x(float *x, float x2, char c)
{
	if (c == '<' && *x <= x2)
	{
		*x += 1;
		return (1);
	}
	else if (c == '>' && *x >= x2)
	{
		*x -= 1;
		return (1);
	}
	return (0);
}

static void	x_inc(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	p;

	xy_init(dt, &x, &y, &p);
	/////////////////////////
	dt->x2 = x2;
	dt->y2 = y2;
	/////////////////////////
	while (x <= x2 || y != y2)
	{
		ft_pixel_put(dt, x, y, ft_blend_color(dt, x, y));
		printf("color %i\n", ft_blend_color(dt, x, y));
		check_x(&x, x2, '<');
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

static void	x_dec(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	p;

	xy_init(dt, &x, &y, &p);
	/////////////////////////
	dt->x2 = x2;
	dt->y2 = y2;
	/////////////////////////
	while (x >= x2 || y != y2)
	{
		ft_pixel_put(dt, x, y, ft_blend_color(dt, x, y));
		printf("color %i\n", ft_blend_color(dt, x, y));
		check_x(&x, x2, '>');
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
	dt->dx = fabs(dt->x1 - x2);
	dt->dy = fabs(dt->y1 - y2);
	if (dt->x1 < x2)
		x_inc(dt, x2, y2);
	else
		x_dec(dt, x2, y2);
}
