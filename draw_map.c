/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:37:13 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/23 16:47:43 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pixel_put(t_fdf *dt, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= dt->sc_w || y < 0 || y >= dt->sc_h)
		return ;
	dst = dt->img.addr + (y * dt->img.size_line) + (x * (dt->img.bpp / 8));
	*(unsigned int *)dst = color;
}

static int	slope1(t_fdf *dt, float x2, float y2)
{
	float	s;

	dt->dx = fabs(x2 - dt->x1);
	dt->dy = fabs(y2 - dt->y1);
	s = dt->dy / dt->dx;
	if (roundf(s) >= 0 && roundf(s) <= 1)
		return (1);
	return (0);
}

static void	choose_line(t_fdf *dt, float x2, float y2)
{
	dt->color.x2 = x2;
	dt->color.y2 = y2;
	dt->color.x1 = dt->x1;
	dt->color.y1 = dt->y1;
	if (!slope1(dt, x2, y2))
		z_line(dt, x2, y2);
	else
		line(dt, x2, y2 );
}

static void	check_draw(t_fdf *dt, int h, int w)
{
	float	y_start;

	dt->z = dt->tab[h][w].z * dt->zm;
	//dt->c = dt->tab[h][w].color;
	if (w + 1 <= dt->width - 1)
		dt->zx = dt->tab[h][w + 1].z * dt->zm;
	if (h + 1 <= dt->height - 1)
		dt->zy = dt->tab[h + 1][w].z * dt->zm;
	y_start = dt->y1;
	//////// h w ////////////////////////////
	dt->color.c1 = dt->tab[h][w].color;
	set_xy1(dt, dt->x1, dt->y1 - dt->z);
	/////// h w+1 ///////////////////////////
	if (w < dt->width - 1)
	{
		dt->color.c2 = dt->tab[h][w + 1].color;
		choose_line(dt, dt->x1 + dt->xsc, y_start - dt->ysc - dt->zx);
	}
	/////// h+1 w ///////////////////////////
	if (h < dt->height - 1)
	{
		dt->color.c2 = dt->tab[h + 1][w].color;
		choose_line(dt, dt->x1 + dt->xsc, y_start + dt->ysc - dt->zy);
	}
	set_xy1(dt, dt->x1 + dt->xsc, dt->y1 + dt->z - dt->ysc);
}

int	draw(t_fdf *dt)
{
	int	w;
	int	h;
	float	x2;
	float	y2;

	h = -1;
	x2 = (dt->sc_w / 5);
	y2 = dt->sc_h / 2 + 100;
	set_xy1(dt, dt->sc_w / 5, dt->sc_h / 2 + 100);
	while (++h < dt->height)
	{
		w = -1;
		while (++w < dt->width)
			check_draw(dt, h, w);
		y2 += dt->ysc;
		x2 += dt->xsc;
		set_xy1(dt, x2, y2);
	}
	mlx_put_image_to_window(dt, dt->win_ptr, dt->img.ptr, x2, y2);
	return (0);
}
