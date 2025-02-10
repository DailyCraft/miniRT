/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:14 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 11:41:24 by dvan-hum         ###   ########.fr       */
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
	t_list	*lst;

	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	init_hooks(data);
	mlx_loop(data->mlx);
	lst = data->cameras;
	while (lst)
	{
		if (((t_camera *) lst->content)->image)
		{
			mlx_destroy_image(data->mlx,
				((t_camera *) lst->content)->image->ptr);
			free(((t_camera *) lst->content)->image);
		}
		lst = lst->next;
	}
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

t_image	*mlx_create_image(t_data *data)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	image->data = (int *) mlx_get_data_addr(image->ptr,
			&image->bits_per_pixel, &image->size_line, &image->endian);
	return (image);
}
