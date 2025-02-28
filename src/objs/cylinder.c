/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:49:04 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/28 11:32:46 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	compute_t_hit(t_ray *ray, t_obj *object)
{
	t_vec	oc;
	t_vec	axis;
	t_vec	dir_perp;
	double	a;
	double	h;

	oc = vec_sub(ray->pos, object->pos);
	axis = object->dir;
	dir_perp = vec_sub(ray->dir, vec_mul(axis, vec_dot(ray->dir, axis)));
	oc = vec_sub(oc, vec_mul(axis, vec_dot(oc, axis)));
	a = vec_dot(dir_perp, dir_perp);
	h = vec_dot(dir_perp, oc);
	return (compute_hit_point(a, -h, &oc, object->cylinder.diameter));
}

bool	inter_cylinder(t_obj *object, t_ray *ray, t_hit *hit)
{
	double	t_hit;
	double	height_at_hit;

	t_hit = compute_t_hit(ray, object);
	if (t_hit == -1)
		return (false);
	hit->pos = ray_at(ray, t_hit);
	height_at_hit = vec_dot(hit->pos, object->dir)
		- vec_dot(object->pos, object->dir);
	if (height_at_hit < 0 || height_at_hit > object->cylinder.height)
		return (false);
	hit->normal = vec_sub(hit->pos, object->pos);
	hit->normal = vec_sub(hit->normal,
			vec_mul(object->dir, vec_dot(hit->normal, object->dir)));
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
	temp = vec_cross(object->dir, cam);
	hit->u = atan2(vec_dot(vec_cross(temp, object->dir), v),
			vec_dot(vec_cross(object->dir, cam), v)) / (2 * M_PI);
	hit->v = vec_dot(object->dir, v) / object->cylinder.height + 1;
}
