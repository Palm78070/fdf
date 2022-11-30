/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:05:52 by rthammat          #+#    #+#             */
/*   Updated: 2022/11/24 16:24:57 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct f_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct f_tab
{
	int	z;
	int	color;
}	t_tab;

typedef struct f_color
{
	int		c1;
	int		c2;
	int		r1;
	int		g1;
	int		b1;
	int		r2;
	int		g2;
	int		b2;
	float		x1;
	float		y1;
	float		x2;
	float		y2;
	float		line_gap;
	float		gap;
	float		gap_ratio;
}	t_color;

typedef struct f_fdf
{
	void	*mlx_ptr;
	int	sc_w;
	int	sc_h;
	void	*win_ptr;
	t_img	img;
	t_color	color;
	t_tab		**tab;
	float		x_start;
	float		y_start;
	float		x1;
	float		y1;
	float		z;
	float		zx;
	float		zy;
	float		dx;
	float		dy;
	int		height;
	int		width;
	float		zm;
	float		xsc;
	float		ysc;
}	t_fdf;

//drawline.c
void	line(t_fdf *dt, float x2, float y2);
//table.c
void	free_tab(t_fdf *dt, t_tab **arr);
void	get_tab(t_fdf *dt, char *file);
//util.c
void	get_map_size(t_fdf *dt, char *input);
void	set_xy1(t_fdf *dt, float x1, float y1);
void	set_projection(t_fdf *dt);
//scale.c
int	find_x_edge(t_fdf *dt);
void	mv_middle(t_fdf *dt, float x_last);
//draw_map.c
void	ft_pixel_put(t_fdf *dt, int x, int y, int color);
int	draw(t_fdf *dt);
//fdf.c
void	free_all(t_fdf *dt);
void	send_err(t_fdf *dt);
//z_axis.c
void	z_line(t_fdf *dt, float x2, float y2);
//color.c
void	insert_color(t_fdf *dt, char *s, int h, int w);
int		offset(t_fdf *dt, float x, float y);
int		ft_blend_color(t_fdf *dt, float x, float y);
//hook.c
int		handle_key(int key_code, t_fdf *dt);
int		handle_cross(t_fdf *dt);
//clear.c
void	free_all(t_fdf *dt);
void	send_err(t_fdf *dt);
void	ft_close(t_fdf *dt, char *s, int n);
#endif
