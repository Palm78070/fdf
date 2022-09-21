/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:05:52 by rthammat          #+#    #+#             */
/*   Updated: 2022/09/19 19:30:50 by rath             ###   ########.fr       */
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

typedef struct f_fdf
{
	void	*mlx_ptr;
	int	sc_w;
	int	sc_h;
	void	*win_ptr;
	int		**tab;
	float		x1;
	float		y1;
	float		z;
	float		dx;
	float		dy;
	int		height;
	int		width;
	int		zm;
	float		xsc;
	float		ysc;
}	t_fdf;

//drawline.c
void	line(t_fdf *dt, float x2, float y2);
//table.c
void	free_tab(t_fdf *dt);
int		**create_tab(t_fdf *dt);
void	fill_tab(t_fdf *dt, char *file);
//draw_map
int		get_height(char *file);
int		get_width(char *file);
void	set_start(t_fdf *dt, float x1, float y1);
//void	draw(t_fdf *dt, int zm);
void	draw2(t_fdf *dt);
//void	draw3(t_fdf *dt, int zm);
void	draw4(t_fdf *dt);
void	isomet(t_fdf *dt, float *x, float *y, int z);
//test.c
void	free_all(t_fdf *dt);
#endif
