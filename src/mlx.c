/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:14 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 08:32:01 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_hooks(t_data *data)
{
	mlx_hook(data->window, DestroyNotify, KeyReleaseMask,
		mlx_loop_end, data->mlx);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_hook, data);
	mlx_expose_hook(data->window, expose_hook, data);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fract-ol");
	init_hooks(data);
	mlx_loop(data->mlx);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
