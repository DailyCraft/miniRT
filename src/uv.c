/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:10:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/28 11:27:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	compute_uv(t_data *data, t_obj *object, t_hit *hit)
{
	if (hit->u != 0 || hit->v != 0)
		return ;
	if (object->type == SPHERE)
		sphere_uv(hit);
	else if (object->type == PLANE)
		plane_uv(hit);
	else if (object->type == CYLINDER)
		cylinder_uv(data, object, hit);
	else if (object->type == TRIANGLE)
		triangle_uv(hit);
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

static float	get_height(t_image *image, int x, int y)
{
	return ((image->data[y * image->width + x] & 0xff) / 127.5 - 1);
}

void	apply_bump(t_data *data, t_hit *hit)
{
	t_image	*image;
	int		x;
	int		y;
	t_color	color;
	t_vec	normal;

	if (!hit->obj->has_bump)
		return ;
	image = hit->obj->bump.image;
	compute_uv(data, hit->obj, hit);
	x = hit->u * image->width;
	y = hit->v * image->height;
	color.color = get_texture_color(data, hit->obj, image, hit);
	if (color.r != color.g || color.r != color.b)
		printf("The bump mapping must contains only shade of gray.\n");
	normal.x = (get_height(image, x + 1, y) - get_height(image, x - 1, y)) / 2;
	normal.y = (get_height(image, x, y + 1) - get_height(image, x, y - 1)) / 2;
	normal.z = -1;
	normalize(&normal);
	hit->normal.x += 20 * normal.x;
	hit->normal.y += 20 * normal.y;
	hit->normal.z += 0.5 * normal.z;
	normalize(&hit->normal);
}

void	get_pixel_color(t_data *data, t_obj *object, t_hit *hit, t_color *color)
{
	t_texture	*texture;

	compute_uv(data, object, hit);
	if (object->has_checkerboard
		&& fmod(floor(hit->u * 50) + floor(hit->v * 50), 2) == 0)
		texture = &object->checkerboard;
	else
		texture = &object->texture;
	if (!texture->image)
		*color = texture->color;
	else
		color->color = get_texture_color(data, object, texture->image, hit);
}
