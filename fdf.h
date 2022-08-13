/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:05:52 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/14 02:15:36 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "mlx/mlx.h"
# include "unistd.h"
# include "fcntl.h"
# include "stdio.h"

typedef struct f_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		**tab;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		height;
	int		width;
}	t_fdf;

//drawline.c
void	line(t_fdf *fdf, int x2, int y2);
int		get_height(char *file);
int		get_width(char *file);
//table.c
void	free_tab(t_fdf *fdf);
int		**create_tab(t_fdf *fdf);
void	fill_tab(t_fdf *fdf, char *file);
//test.c
void	free_all(t_fdf *fdf);
#endif
