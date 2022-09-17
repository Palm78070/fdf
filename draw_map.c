/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:37:13 by rthammat          #+#    #+#             */
/*   Updated: 2022/09/18 00:26:19 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *file)
{
	int	fd;
	int	count;
	char	*s;

	fd = open(file, O_RDONLY);
	count = 0;
	if (fd < 0)
	{
		perror("error");
		return (-1);
	}
	s = get_next_line(fd);
	while (s != NULL)
	{
		++count;
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	if (close(fd) == -1)
		perror("error");
	return (count);
}

int	get_width(char *file)
{
	int	fd;
	int	count;
	char	*s;
	char	**s2;

	fd = open(file, O_RDONLY);
	count = 0;
	if (fd < 0)
	{
		perror("error");
		return (-1);
	}
	s = get_next_line(fd);
	if (s != NULL)
	{
		int i = -1;
		s2 = ft_split(s, ' ');
		while (s2[++i])
			++count;
		free_double(s2);
	}
	while (s != NULL)
		s = get_next_line(fd);
	free(s);
	if (close(fd) == -1)
		perror("error");
	return (count);
}

void	set_start(t_fdf *dt, float x, float y)
{
	dt->x1 = x;
	dt->y1 = y;
}

/*void	draw(t_fdf *dt, int zm)
{
	int	w;
	int	h;
	float	x2;
	float	y2;

	h = -1;
	x2 = (dt->sc_w / 2);
	y2 = dt->sc_h / 2;
	set_start(dt, dt->sc_w / 2, dt->sc_h / 2);
	while (++h < dt->height - 1)
	{
		w = -1;
		while (++w < dt->width - 1)
		{
			dt->z1 = dt->tab[h][w];
			if (dt->z1 == 0)
			{
				line(dt, dt->x1 + zm, dt->y1 + zm * dt->rt);
				line(dt, dt->x1 - zm, dt->y1 + zm * dt->rt);
			}
			set_start(dt, dt->x1 + zm, dt->y1 + zm * dt->rt);
		}
		set_start(dt, x2, y2);
		y2 += (zm * dt->rt);
		x2 -= zm;
	}
}*/

void	draw2(t_fdf *dt)
{
	int	w;
	int	h;

	h = -1;
	set_start(dt, dt->sc_w / 2, 0);
	while (++h < dt->height - 1)
	{
		w = -1;
		while (++w < dt->width - 1)
		{
			line(dt, dt->x1 + dt->zm, dt->y1);
			line(dt, dt->x1, dt->y1 + dt->zm);
			set_start(dt, dt->x1 + dt->zm, dt->y1);
		}
		set_start(dt, dt->sc_w / 2, dt->y1 + dt->zm - 1);
	}
}

void	dummy(t_fdf *dt, float x2, float y2)
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
	/*printf("x1 %f\n", dt->x1);
	printf("y1 %f\n", dt->y1);
	printf("x2 %f\n", x2);
	printf("y2 %f\n", y2);*/
	//printf("dx %f\n", dt->dx);
	//printf("dy %f\n", dt->dy);
	s = round(dt->dy / dt->dx);
	//printf("slope %f\n", s);
	x_start = dt->x1;
	y_start = dt->y1;
	while (dt->x1 < x2)
	{
		line(dt, dt->x1 + 0.1, dt->y1 - s);
		set_start(dt, dt->x1 + 1, dt->y1 - s);
	}
	set_start(dt, x_start, y_start);
}

void	check_draw(t_fdf *dt, int h, int w)
{
	int	zm;

	zm = dt->zm;
	if (dt->tab[h][w] != 0)
	{
		set_start(dt, dt->x1, dt->y1 - 190);
		/*if (h == 2 && w == 11)
		{
			line(dt, dt->x1, dt->y1 - 100);
			//printf("x1 %f y1 %f\n", dt->x1, dt->y1 - 190);
		}*/
		if (dt->tab[h][w + 1] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		if (dt->tab[h + 1][w] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		set_start(dt, dt->x1, dt->y1 + 190);
	}
	if (dt->tab[h][w] == 0)
	{
		if (dt->tab[h + 1][w] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		if (dt->tab[h][w + 1] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		/*if (dt->tab[h + 1][w] != 0) ////try
			dummy(dt, dt->x1 + dt->xsc, dt->y1 - 180);
		if (dt->tab[h][w + 1] != 0) ///try
			dummy(dt, dt->x1 + dt->xsc, dt->y1 - 190);*/
			//line(dt, dt->x1, dt->y1 - 190);
		if (h != 0 && dt->tab[h - 1][w] != 0) ////try
		{
			printf("h %d w %d\n", h, w);
			if (h == 3 && w == 11)
				dummy(dt, dt->x1 + dt->xsc, dt->y1 - 190);
			//dummy(dt, dt->x1 + dt->xsc, dt->y1 - 190);
			//line(dt, dt->x1, dt->y1 - zm - 80);
		}
		/*if (w != 0 && dt->tab[h][w - 1] != 0) ///try
			line(dt, dt->x1, dt->y1 - zm - 80);*/
	}
	set_start(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
}

/*void	draw3(t_fdf *dt, int zm)
{
	int	w;
	int	h;
	float	x2;
	float	y2;

	h = -1;
	x2 = (dt->sc_w / 5);
	y2 = dt->sc_h / 2 + 100;
	set_start(dt, dt->sc_w / 5, dt->sc_h / 2 + 100);
	while (++h < dt->height - 1)
	{
		w = -1;
		while (++w < dt->width - 1)
			check_draw(dt, h, w);
		set_start(dt, dt->x1, dt->y1 - 1); //////////////close
		line(dt, dt->x1 + zm, dt->y1 + zm * dt->rt); /////////close
		y2 += (zm * dt->rt);
		x2 += zm;
		set_start(dt, x2, y2);
	}
////////////////////////////////////////////////////////////////
	w = -1;
	while (++w < dt->width - 1)
	{
		line(dt, dt->x1 + zm, dt->y1 - zm * dt->rt);
		set_start(dt, dt->x1 + zm, dt->y1 - zm * dt->rt);
	}
////////////////////////////////////////////////////////////////
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
	set_start(dt, dt->sc_w / 5, dt->sc_h / 2 + 100);
	while (++h < dt->height - 1)
	{
		w = -1;
		while (++w < dt->width - 1)
			check_draw(dt, h, w);
		set_start(dt, dt->x1, dt->y1 - 1); //////////////close
		line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc); /////////close
		y2 += dt->ysc;
		x2 += dt->xsc;
		set_start(dt, x2, y2);
	}
////////////////////////////////////////////////////////////////
	w = -1;
	while (++w < dt->width - 1)
	{
		line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		set_start(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
	}
////////////////////////////////////////////////////////////////
}

void	isomet(t_fdf *dt, float *x, float *y, int z)
{
	(void)dt;
	*x = (*x - *y) * cos(0.5236);
	*y = (*x + *y) * sin(0.5236) - z;
}