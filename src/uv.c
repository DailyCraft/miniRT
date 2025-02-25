/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:10:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/25 20:43:37 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sphere_uv(t_hit *hit)
{
	hit->u = atan2(hit->normal.x, hit->normal.z) / (2 * M_PI) + 0.5;
	hit->v = acos(hit->normal.y) / M_PI;
}

static void	cylinder_uv(t_data *data, t_obj *object, t_hit *hit)
{
	t_vec	v;
	t_vec	cam;
	t_vec	temp;

	v = vec_sub(object->pos, hit->pos);
	cam = ((t_camera *) data->cameras->content)->dir;
	temp = vec_cross(&object->dir, &cam);
	hit->u = atan2(vec_dot(vec_cross(&object->dir, &cam), v),
			vec_dot(vec_cross(&temp, &object->dir), v)) / (2 * M_PI) + 0.5;
	hit->v = vec_dot(object->dir, v) / object->cylinder.height + 1;
}

static void	plane_uv(t_hit *hit)
{
	t_vec	u;
	t_vec	v;

	if (fabs(hit->normal.x) > fabs(hit->normal.y))
		u = (t_vec){-hit->normal.z, 0, hit->normal.x};
	else
		u = (t_vec){0, hit->normal.z, -hit->normal.y};
	normalize(&u);
	v = vec_cross(&hit->normal, &u);
	normalize(&v);
	hit->u = vec_dot(hit->pos, u) * 0.05;
	hit->v = vec_dot(hit->pos, v) * 0.05;
	hit->u -= floor(hit->u);
	hit->v -= floor(hit->v);
}

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

int	get_pixel_color(t_data *data, t_obj *object, t_hit *hit)
{
	if (object->has_checkerboard
		&& fmod(floor(hit->u * 50) + floor(hit->v * 50), 2) == 0)
	{
		if (object->checkerboard.is_color)
			return (object->checkerboard.color.color);
		return (get_texture_color(data, object,
				object->checkerboard.image, hit));
	}
	if (object->texture.is_color)
		return (object->texture.color.color);
	return (get_texture_color(data, object, object->texture.image, hit));
}
