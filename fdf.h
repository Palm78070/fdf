/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:05:52 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/15 02:41:55 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "mlx/mlx.h"
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

typedef struct f_fdf
{
	void	*mlx_ptr;
	int	sc_w;
	int	sc_h;
	void	*win_ptr;
	t_img	img;
	t_tab		**tab;
	int		c;
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

//drawline.c:w

void	line(t_fdf *dt, float x2, float y2);
//table.c
void	free_tab(t_fdf *dt, t_tab **arr);
///////////////////////////////////////
void	clear_tab(t_tab **arr, int i);
///////////////////////////////////////
//int		**create_tab(t_fdf *dt);
t_tab		**create_tab(t_fdf *dt);
void	get_tab(t_fdf *dt, char *file);
//map_uti.c
int		get_height(char *file);
int		get_width(char *file);
void	get_map_size(t_fdf *dt, char *input);
void	set_start(t_fdf *dt, float x1, float y1);
//draw_map
void	draw4(t_fdf *dt);
//test.c
void	free_all(t_fdf *dt);
void	send_err(t_fdf *dt);
//z_axis.c
void	z_line(t_fdf *dt, float x2, float y2);
//color.c
int	convert_hex(char *s);
int	found_c(char *str, char c);
void	insert_color(t_fdf *dt, char *s, int h, int w);
//void	fill_color(t_fdf *dt, char *file);
//void	fill_color(t_fdf *dt, char *s, int h, int w);
#endif
