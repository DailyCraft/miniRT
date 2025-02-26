/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:48:12 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 10:01:01 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	calculate_hit_point(double *hit, double disc, double h, double a)
{
	double	t1;
	double	t2;
	double	sqrt_disc;

	sqrt_disc = sqrt(disc);
	t1 = (h - sqrt_disc) / a;
	t2 = (h + sqrt_disc) / a;
	if (t1 > 0.0001)
		*hit = t1;
	else if (t2 > 0.0001)
		*hit = t2;
	else
		return (false);
	return (true);
}

static bool	inter_sphere(t_obj *object, t_ray *ray, t_hit *hit)
{
	t_vec	oc;
	double	radius;
	double	a;
	double	h;
	double	t_hit;
	double	discriminant;

	oc = vec_sub(object->pos, ray->pos);
	radius = object->sphere.diameter / 2.0;
	a = vec_dot(ray->dir, ray->dir);
	h = vec_dot(ray->dir, oc);
	discriminant = h * h - a * (vec_dot(oc, oc) - radius * radius);
	if (!calculate_hit_point(&t_hit, discriminant, h, a))
		return (false);
	hit->pos = ray_at(ray, t_hit);
	hit->normal = vec_sub(hit->pos, object->pos);
	normalize(&hit->normal);
	return (true);
}

static bool	inter_plane(t_obj *object, t_ray *ray, t_hit *hit)
{
	double	denom;
	double	t;

	denom = vec_dot(ray->dir, object->dir);
	if (fabs(denom) < 0.0001)
		return (false);
	t = -(vec_dot(object->dir, vec_sub(ray->pos, object->pos))) / denom;
	if (t < 0.0001)
		return (false);
	hit->pos = ray_at(ray, t);
	if (denom < 0)
		hit->normal = object->dir;
	else
		hit->normal = vec_mul(&object->dir, -1);
	normalize(&hit->normal);
	return (true);
}

t_vec	vec_scale(t_vec *v, double s)
{
	t_vec	result;

	result.x = v->x * s;
	result.y = v->y * s;
	result.z = v->z * s;
	return (result);
}

static bool	inter_cylinder(t_obj *object, t_ray *ray, t_hit *hit)
{
	t_vec	oc;
	t_vec	axis;
	t_vec	dir_perp;
	t_vec	oc_perp;
	double	radius;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_disc;
	double	t1;
	double	t2;
	double	t_hit;
	double	height_at_hit;

	oc = vec_sub(ray->pos, object->pos);
	radius = object->cylinder.diameter / 2.0;
	axis = object->dir;
	dir_perp = vec_sub(ray->dir, vec_scale(&axis, vec_dot(ray->dir, axis)));
	oc_perp = vec_sub(oc, vec_scale(&axis, vec_dot(oc, axis)));
	a = vec_dot(dir_perp, dir_perp);
	b = vec_dot(dir_perp, oc_perp);
	c = vec_dot(oc_perp, oc_perp) - radius * radius;
	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrt(discriminant);
	t1 = (-b - sqrt_disc) / (a);
	t2 = (-b + sqrt_disc) / (a);
	t_hit = (t1 > 0.0001) ? t1 : (t2 > 0.0001 ? t2 : -1);
	if (t_hit < 0)
		return (false);
	hit->pos = ray_at(ray, t_hit);
	height_at_hit = vec_dot(hit->pos, axis) - vec_dot(object->pos, axis);
	if (height_at_hit < 0 || height_at_hit > object->cylinder.height)
		return (false);
	hit->normal = vec_sub(hit->pos, object->pos);
	hit->normal = vec_sub(hit->normal, vec_scale(&axis, vec_dot(hit->normal, axis)));
	normalize(&hit->normal);
	return (true);
}

bool	intersect(t_obj *object, t_ray *ray, t_hit *hit)
{
	hit->obj = object;
	return (
		(object->type == SPHERE && inter_sphere(object, ray, hit))
		|| (object->type == PLANE && inter_plane(object, ray, hit))
		|| (object->type == CYLINDER && inter_cylinder(object, ray, hit))
		|| (object->type == TRIANGLE && false)
		|| (object->type == CONE && false)
	);
}
