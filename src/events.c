/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:17:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/14 13:06:12 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	change_cam(t_data *data)
{
	t_list	*first;

	first = data->cameras;
	data->cameras = first->next;
	first->next = NULL;
	ft_lstadd_back(&data->cameras, first);
}

int	key_hook(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_loop_end(data->mlx);
		return (0);
	}
	else if (key == XK_c)
		change_cam(data);
	expose_hook(data);
	return (0);
}

int	expose_hook(t_data *data)
{
	t_camera	*camera;

	mlx_string_put(data->mlx, data->window,
		WIDTH / 2, HEIGHT / 2, 0xffffff, "Loading...");
	camera = data->cameras->content;
	update_image(data, camera);
	mlx_put_image_to_window(data->mlx, data->window, camera->image->ptr, 0, 0);
	return (0);
}
