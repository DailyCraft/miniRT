/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:49:04 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/27 17:15:34 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	calculate_discriminant(t_ray *ray, t_obj *object,
	double *a, double *h)
{
	t_vec	oc;
	t_vec	axis;
	t_vec	dir_perp;
	t_vec	oc_perp;

	oc = vec_sub(ray->pos, object->pos);
	axis = object->dir;
	dir_perp = vec_sub(ray->dir, vec_mul(&axis, vec_dot(ray->dir, axis)));
	oc_perp = vec_sub(oc, vec_mul(&axis, vec_dot(oc, axis)));
	*a = vec_dot(dir_perp, dir_perp);
	*h = vec_dot(dir_perp, oc_perp);
	return (*h * *h - *a * (vec_dot(oc_perp, oc_perp)
			- squale(object->cylinder.diameter / 2.0)));
}

static bool	check_hit_height(t_hit *hit, t_ray *ray,
	t_obj *object, double t_hit)
{
	double	height_at_hit;

	hit->pos = ray_at(ray, t_hit);
	height_at_hit = vec_dot(hit->pos, object->dir)
		- vec_dot(object->pos, object->dir);
	if (height_at_hit < 0 || height_at_hit > object->cylinder.height)
		return (false);
	return (true);
}

bool	inter_cylinder(t_obj *object, t_ray *ray, t_hit *hit)
{
	t_vec	axis;
	double	discriminant;
	double	t_hit;
	double	a;
	double	h;

	axis = object->dir;
	discriminant = calculate_discriminant(ray, object, &a, &h);
	if (discriminant < 0)
		return (false);
	if (!calculate_hit_point(&t_hit, discriminant, -h, a))
		return (false);
	if (!check_hit_height(hit, ray, object, t_hit))
		return (false);
	hit->normal = vec_sub(hit->pos, object->pos);
	hit->normal = vec_sub(hit->normal,
			vec_mul(&axis, vec_dot(hit->normal, axis)));
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
