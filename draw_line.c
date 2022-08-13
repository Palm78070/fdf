/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/14 02:18:09 by rthammat         ###   ########.fr       */
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

void	line(t_fdf *fdf, int x2, int y2)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;

	x = fdf->x1;
	y = fdf->y1;
	dx = x2 - fdf->x1;
	dy = y2 - fdf->y1;
	if (dy < 0)
		dy *= -1;
	p = (2 * dy) - dx;
	while (x <= x2)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xFFFFFF);
		++x;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - (2 * dx);
			if (fdf->y1 <= y2)
				++y;
			else
				--y;
		}
	}
}

/*void	set_start(t_fdf *fdf, int x, int y)
{
	fdf->x1 = x;
	fdf->y1 = y;
}

void	draw(t_fdf *fdf)
{
	set_start(fdf, 0, 0);
	while (fdf->y1 < fdf->height)
	{
		fdf->x1 = 0;
		while (fdf->x1 < fdf->width)
		{
			fdf->x2 = fdf->x1 + 1;
			fdf->y2 = fdf->y1;
			line(fdf);
			fdf->x2 = fdf->x1;
			fdf->y2 = fdf->y1 + 1;
			line(fdf);
			fdf->x1 += 1;
		}
		fdf->y1 += 1;
	}
}*/

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
