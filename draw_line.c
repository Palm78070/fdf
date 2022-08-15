/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/15 21:05:59 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	line(t_fdf *fdf)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;

	x = fdf->x1;
	y = fdf->y1;
	dx = fdf->x2 - fdf->x1;
	dy = fdf->y2 - fdf->y1;
	if (dy < 0)
		dy *= -1;
	p = (2 * dy) - dx;
	while (x <= fdf->x2)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xFFFFFF);
		++x;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - (2 * dx);
			if (fdf->y1 <= fdf->y2)
				++y;
			else
				--y;
		}
	}
}*/

void	line(t_fdf *dt, int x2, int y2)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;

	x2 *= dt->zm;
	y2 *= dt->zm;
	x = (dt->x1) * dt->zm;
	y = (dt->y1) * dt->zm;
	//dx = x2 - fdf->x1;
	//dy = y2 - fdf->y1;
	dx = x2 - x;
	dy = y2 - y;
	if (dy < 0)
		dy *= -1;
	p = (2 * dy) - dx;
	while (x <= x2 || y != y2)
	{
		//if (y2 == (dt->y1 + 1) * dt->zm)
		//	printf("xxx\n");
		mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, 0xFFFFFF);
		if (x <= x2)
			++x;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - (2 * dx);
			if ((dt->y1 * dt->zm) <= y2 && y != y2)
				++y;
			else if (y != y2)
				--y;
		}
	}
}

void	set_start(t_fdf *dt, int x, int y)
{
	dt->x1 = x;
	dt->y1 = y;
}

void	draw(t_fdf *dt)
{
	int	height;
	int	width;
	int	start;

	start = dt->sc_w / (2 * dt->zm) - (dt->width / 2);
	printf("start %i\n", start);
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
			dt->x1 += 1;
		}
		dt->y1 += 1;
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
