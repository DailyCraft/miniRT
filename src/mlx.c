/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:14 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:53:23 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_data *data)
{
	printf("Starting minilibx...\n");
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	init_images(data);
	mlx_hook(data->window, DestroyNotify, KeyReleaseMask,
		mlx_loop_end, data->mlx);
	mlx_key_hook(data->window, key_hook, data);
	mlx_mouse_hook(data->window, mouse_hook, data);
	mlx_expose_hook(data->window, expose_hook, data);
	mlx_loop(data->mlx);
	free_images(data);
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
	image->width = WIDTH;
	image->height = HEIGHT;
	return (image);
}
