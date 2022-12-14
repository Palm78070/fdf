/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 01:56:08 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/14 01:56:32 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_all(t_fdf *dt)
{
	if (dt)
	{
		if (dt->img.ptr)
			mlx_destroy_image(dt->mlx_ptr, dt->img.ptr);
		if (dt->win_ptr)
			mlx_destroy_window(dt->mlx_ptr, dt->win_ptr);
		if (dt->mlx_ptr)
			free(dt->mlx_ptr);
	}
	if (dt->tab != NULL)
		free_tab(dt, dt->tab);
	free(dt);
}

void	send_err(t_fdf *dt)
{
	perror("error");
	free_all(dt);
	exit(1);
}

void	ft_close(t_fdf *dt, char *s, int n)
{
	ft_putstr_fd(s, n);
	free_all(dt);
	exit(0);
}
