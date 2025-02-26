/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:53:05 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:53:49 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_textures(t_data *data, bool contains, t_texture *texture)
{
	if (!contains || !texture->image_path)
		return ;
	texture->image = malloc(sizeof(t_image));
	texture->image->ptr = mlx_xpm_file_to_image(data->mlx, texture->image_path,
			&texture->image->width, &texture->image->height);
	texture->image->data = (int *) mlx_get_data_addr(texture->image->ptr,
			&texture->image->bits_per_pixel, &texture->image->size_line,
			&texture->image->endian);
	ft_free_set((void **) &texture->image_path, NULL);
}

void	init_images(t_data *data)
{
	t_list	*lst;
	t_obj	*obj;

	lst = data->objects;
	while (lst)
	{
		obj = lst->content;
		init_textures(data, true, &obj->texture);
		init_textures(data, obj->has_bump, &obj->bump);
		init_textures(data, obj->has_checkerboard, &obj->checkerboard);
		lst = lst->next;
	}
}

static void	free_textures(t_data *data, t_obj *obj)
{
	if (obj->texture.image)
	{
		mlx_destroy_image(data->mlx, obj->texture.image->ptr);
		free(obj->texture.image);
	}
	if (obj->bump.image)
	{
		mlx_destroy_image(data->mlx, obj->bump.image->ptr);
		free(obj->bump.image);
	}
	if (obj->checkerboard.image)
	{
		mlx_destroy_image(data->mlx, obj->checkerboard.image->ptr);
		free(obj->checkerboard.image);
	}
}

void	free_images(t_data *data)
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
		free_textures(data, lst->content);
		lst = lst->next;
	}
}
