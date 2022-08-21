/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/21 21:04:24 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	line(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	p;

	x2 *= dt->zm;
	y2 *= dt->zm;
	x = (dt->x1) * dt->zm;
	y = (dt->y1) * dt->zm;
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
			if ((dt->y1 * dt->zm) <= y2 && y != y2)
			{
				if (y >= y2 && x > x2)
					break ;
				++y;
			}
			else if (y != y2)
			{
				if (y <= y2 && x > x2)
					break ;
				--y;
			}
		}
	}
}*/

int	check_y_inc(float x, float x2, float y, float y2)
{
	if (y >= y2 && x > x2)
		return (0);
	return (1);
}

int	check_y_dec(float x, float x2, float y, float y2)
{
	if (y <= y2 && x > x2)
		return (0);
	return (1);
}

void	x_inc(t_fdf *dt, float x2, float y2)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	p;

	//x2 *= dt->zm;
	//y2 *= dt->zm;
	//x = (dt->x1) * dt->zm;
	//y = (dt->y1) * dt->zm;
	x = (dt->x1);
	y = (dt->y1);
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
			if ((dt->y1 * dt->zm) <= y2)
			{
				if (y++ >= y2 && x > x2)
					break ;
			}
			else
			{
				if (y-- <= y2 && x > x2)
					break ;
			}
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

	//x2 *= dt->zm;
	//y2 *= dt->zm;
	//x = (dt->x1) * dt->zm;
	//y = (dt->y1) * dt->zm;
	x = (dt->x1);
	y = (dt->y1);
	dx = x - x2;
	dy = y - y2;
	if (dy < 0)
		dy *= -1;
	p = (2 * dy) - dx;
	while (x >= x2 || y != y2)
	{
		//printf("x %f\n", x);
		//printf("y %f\n", y);
		mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
		if (x >= x2)
			--x;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - (2 * dx);
			if ((dt->y1 * dt->zm) <= y2)
			{
				if (y++ >= y2 && x < x2)
					break ;
			}
			else
			{
				if (y-- <= y2 && x < x2)
					break ;
			}
		}
	}
	//printf("dec x %f\n", x);
	//printf("dec y %f\n", y);
	//printf("dec y2 %f\n", y2);
}

void	line(t_fdf *dt, float x2, float y2)
{
	if (dt->x1 < x2)
		x_inc(dt, x2, y2);
	else
		x_dec(dt, x2, y2);
}

void	set_start(t_fdf *dt, float x, float y)
{
	dt->x1 = x;
	dt->y1 = y;
}

/*void	draw(t_fdf *dt)
{
	float	height;
	float	width;
	float	start;

	start = dt->sc_w / (2 * dt->zm) - (dt->width / 2);
	//printf("start %i\n", start);
	set_start(dt, start, 0);
	height = dt->height + dt->y1;
	width = dt->width + dt->x1;
	while (dt->y1 < height)
	{
		dt->x1 = start;
		while (dt->x1 < width)
		{
			line(dt, dt->x1 + 1, dt->y1);
			line(dt, dt->x1, dt->y1 + 1);
			//line(dt, dt->x1 + 1, dt->y1 * tan(0.5236));
			//line(dt, dt->x1 - 1, (dt->y1) * tan(0.5236));
			dt->x1 += 1;
		}
		dt->y1 += 1;
	}
}*/

void	draw(t_fdf *dt, int zm)
{
	int	w;
	int	h;
	float	x2;
	float	y2;

	h = -1;
	x2 = (dt->sc_w / 2) + zm;
	y2 = 20 * dt->rt;
	set_start(dt, dt->sc_w / 2, 0);
	while (++h < dt->height - 1)
	{
		w = -1;
		while (++w < dt->width - 1)
		{
			line(dt, dt->x1 - zm, dt->y1 + zm * dt->rt);
			line(dt, dt->x1 + zm, dt->y1 + zm * dt->rt);
			set_start(dt, dt->x1 - zm, dt->y1 + zm * dt->rt);
		}
		set_start(dt, x2, y2);
		y2 += (zm * dt->rt);
		x2 += zm;
	}
}

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
