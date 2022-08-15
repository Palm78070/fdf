/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:05:52 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/15 21:16:36 by rath             ###   ########.fr       */
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
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		height;
	int		width;
	int		zm;
}	t_fdf;

//drawline.c
void	line(t_fdf *dt, int x2, int y2);
void	set_start(t_fdf *dt, int x1, int y1);
void	draw(t_fdf *dt);
int		get_height(char *file);
int		get_width(char *file);
//table.c
void	free_tab(t_fdf *dt);
int		**create_tab(t_fdf *dt);
void	fill_tab(t_fdf *dt, char *file);
//test.c
void	free_all(t_fdf *dt);
#endif
