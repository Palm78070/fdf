/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:05:52 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/11 19:40:34 by rthammat         ###   ########.fr       */
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
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	height;
}	t_fdf;

void	draw_line(t_fdf *fdf);
int	get_height(char *file);

#endif
