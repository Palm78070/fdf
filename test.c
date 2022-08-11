/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/11 19:40:31 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 500,500, "mlx 42");
	fdf->x1 = 0;
	fdf->y1 = 0;
	fdf->x2 = 500;
	fdf->y2 = 500;
	fdf->height = 0;
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc <= 1)
	{
		ft_putstr_fd("No file argument included\n", 2);
		exit(1);
	}
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		exit(1);
	fdf_init(fdf);
	fdf->height = get_height(argv[1]);
	printf("height is %i\n", fdf->height);
	/*draw_line(fdf);
	fdf->x1 = 0;
	fdf->y1 = 500;
	fdf->x2 = 500;
	fdf->y2 = 0;
	draw_line(fdf);
	mlx_loop(fdf->mlx_ptr);*/
	free(fdf);
	return (0);
}
