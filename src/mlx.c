/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:14 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 16:06:27 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_images(t_data *data)
{
	t_list		*lst;
	t_object	*object;
	int			useless;

	lst = data->objects;
	while (lst)
	{
		object = lst->content;
		if (object->bump_path)
		{
			object->bump = malloc(sizeof(t_image));
			object->bump->ptr = mlx_xpm_file_to_image(data->mlx,
					object->bump_path, &useless, &useless);
			object->bump->data = (int *) mlx_get_data_addr(object->bump->ptr,
					&object->bump->bits_per_pixel, &object->bump->size_line,
					&object->bump->endian);
			free(object->bump_path);
		}
		lst = lst->next;
	}
}

static void	init_hooks(t_data *data)
{
	mlx_hook(data->window, DestroyNotify, KeyReleaseMask,
		mlx_loop_end, data->mlx);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_hook, data);
	mlx_expose_hook(data->window, expose_hook, data);
}

static void	free_images(t_data *data)
{
	t_list	*lst;

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
	lst = data->objects;
	while (lst)
	{
		if (((t_object *) lst->content)->bump)
		{
			mlx_destroy_image(data->mlx,
				((t_object *) lst->content)->bump->ptr);
			free(((t_object *) lst->content)->bump);
		}
		lst = lst->next;
	}
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	init_images(data);
	init_hooks(data);
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
	return (image);
}
