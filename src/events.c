/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:17:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 14:08:14 by dvan-hum         ###   ########.fr       */
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

static void	move(t_data *data, int key)
{
	t_camera	*camera;
	t_vec		temp;

	camera = data->cameras->content;
	if (key == XK_w || key == XK_s)
	{
		temp = vec_mul(&camera->dir, 10 - 20 * (key == XK_s));
		camera->pos = vec_add(&camera->pos, &temp);
	}
	else if (key == XK_a || key == XK_d)
	{
		ft_memset(&temp, 0, sizeof(t_vec));
		if (camera->dir.x == 0 && camera->dir.y == 1 && camera->dir.z == 0)
			temp.x = 1;
		else
		{
			temp.y = 1;
			temp = vec_cross(&camera->dir, &temp);
		}
		temp = vec_mul(&temp, 10 - 20 * (key == XK_a));
		camera->pos = vec_add(&camera->pos, &temp);
	}
	else if (key == XK_space || key == XK_Shift_L)
		camera->pos.y += 10 - 20 * (key == XK_Shift_L);
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
	else
		move(data, key);
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
