/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:17:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 13:20:00 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int key, t_data *data)
{
	if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	else if (key == XK_c)
	{
	}
	return (0);
}

int	expose_hook(t_data *data)
{
	t_camera	*camera;
	int			y;
	int			x;

	camera = data->cameras->content;
	camera->image = mlx_create_image(data);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			camera->image->data[y * WIDTH + x] = get_color(data, camera, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->window, camera->image->ptr, 0, 0);
	return (0);
}
