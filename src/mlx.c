/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:14 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/25 20:41:25 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO add new fonction for images: texture, bump, checkboard.
static void	init_images(t_data *data)
{
	t_list	*lst;
	t_obj	*object;

	lst = data->objects;
	while (lst)
	{
		object = lst->content;
		if (object->has_bump)
		{
			object->bump.image = malloc(sizeof(t_image));
			object->bump.image->ptr = mlx_xpm_file_to_image(data->mlx,
					object->bump.image_path, &object->bump.image->width,
					&object->bump.image->height);
			object->bump.image->data = (int *)
				mlx_get_data_addr(object->bump.image->ptr,
					&object->bump.image->bits_per_pixel,
					&object->bump.image->size_line,
					&object->bump.image->endian);
			ft_free_set((void **) &object->bump.image_path, NULL);
		}
		lst = lst->next;
	}
}

static void	init_textures(t_data *data)
{
	t_list	*lst;
	t_obj	*object;

	lst = data->objects;
	while (lst)
	{
		object = lst->content;
		if (object->texture.is_color == false)
		{
			printf("%s", object->texture.image_path);
			object->texture.image = malloc(sizeof(t_image));
			object->texture.image->ptr = mlx_xpm_file_to_image(data->mlx,
					object->texture.image_path, &object->texture.image->width,
					&object->texture.image->height);
			object->texture.image->data = (int *)
				mlx_get_data_addr(object->texture.image->ptr,
					&object->texture.image->bits_per_pixel,
					&object->texture.image->size_line,
					&object->texture.image->endian);
			ft_free_set((void **) &object->texture.image_path, NULL);
		}
		lst = lst->next;
	}
}

// static void	free_images(t_data *data)
// {
// 	t_list	*lst;

// 	lst = data->cameras;
// 	while (lst)
// 	{
// 		if (((t_camera *) lst->content)->image)
// 		{
// 			mlx_destroy_image(data->mlx,
// 				((t_camera *) lst->content)->image->ptr);
// 			free(((t_camera *) lst->content)->image);
// 		}
// 		lst = lst->next;
// 	}
// 	lst = data->objects;
// 	while (lst)
// 	{
// 		if (((t_obj *) lst->content)->bump)
// 		{
// 			mlx_destroy_image(data->mlx,
// 				((t_obj *) lst->content)->bump->ptr);
// 			free(((t_obj *) lst->content)->bump);
// 		}
// 		lst = lst->next;
// 	}
// }

//TODO FIX free images
void	init_mlx(t_data *data)
{
	printf("Starting minilibx...\n");
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	init_images(data);
	init_textures(data);
	mlx_hook(data->window, DestroyNotify, KeyReleaseMask,
		mlx_loop_end, data->mlx);
	mlx_key_hook(data->window, key_hook, data);
	mlx_mouse_hook(data->window, mouse_hook, data);
	mlx_expose_hook(data->window, expose_hook, data);
	mlx_loop(data->mlx);
	//free_images(data);
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
