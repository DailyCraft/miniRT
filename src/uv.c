/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:10:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:52:03 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	compute_uv(t_data *data, t_obj *object, t_hit *hit)
{
	if (object->type == SPHERE)
		sphere_uv(hit);
	else if (object->type == PLANE)
		plane_uv(hit);
	else if (object->type == CYLINDER)
		cylinder_uv(data, object, hit);
}

static int	get_texture_color(t_data *data, t_obj *object,
	t_image *texture, t_hit *hit)
{
	int	x;
	int	y;

	compute_uv(data, object, hit);
	x = hit->u * texture->width;
	y = hit->v * texture->height;
	return (texture->data[y * texture->width + x]);
}

void	get_pixel_color(t_data *data, t_obj *object, t_hit *hit, t_color *color)
{
	if (object->has_checkerboard
		&& fmod(floor(hit->u * 50) + floor(hit->v * 50), 2) == 0)
	{
		if (!object->checkerboard.image)
			*color = object->checkerboard.color;
		else
			color->color = get_texture_color(data, object,
					object->checkerboard.image, hit);
	}
	else
	{
		if (!object->texture.image)
			*color = object->texture.color;
		else
			color->color = get_texture_color(data, object,
					object->texture.image, hit);
	}
}
