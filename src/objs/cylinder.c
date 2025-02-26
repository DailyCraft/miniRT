/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:49:04 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 22:26:02 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO NORM
bool	inter_cylinder(t_obj *object, t_ray *ray, t_hit *hit)
{
	t_vec	oc;
	t_vec	axis;
	t_vec	dir_perp;
	t_vec	oc_perp;
	double	radius;
	double	a;
	double	h;
	double	c;
	double	discriminant;
	double	t_hit;
	double	height_at_hit;

	oc = vec_sub(ray->pos, object->pos);
	radius = object->cylinder.diameter / 2.0;
	axis = object->dir;
	dir_perp = vec_sub(ray->dir, vec_mul(&axis, vec_dot(ray->dir, axis)));
	oc_perp = vec_sub(oc, vec_mul(&axis, vec_dot(oc, axis)));
	a = vec_dot(dir_perp, dir_perp);
	h = vec_dot(dir_perp, oc_perp);
	c = vec_dot(oc_perp, oc_perp) - radius * radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	if (!calculate_hit_point(&t_hit, discriminant, -h, a))
		return (false);
	hit->pos = ray_at(ray, t_hit);
	height_at_hit = vec_dot(hit->pos, axis) - vec_dot(object->pos, axis);
	if (height_at_hit < 0 || height_at_hit > object->cylinder.height)
		return (false);
	hit->normal = vec_sub(hit->pos, object->pos);
	hit->normal = vec_sub(hit->normal, vec_mul(&axis, vec_dot(hit->normal, axis)));
	normalize(&hit->normal);
	return (true);
}

void	cylinder_uv(t_data *data, t_obj *object, t_hit *hit)
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
