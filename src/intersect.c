/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:48:12 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/14 09:40:58 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	inter_sphere(t_object *object, t_ray *ray, t_hit *hit)
{
	t_vec	oc;
	float	radius;
	float	a;
	float	h;
	float	c;
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	t_hit;

	oc = vec_sub(&object->pos, &ray->pos);
	radius = object->sphere.diameter / 2.0;
	a = vec_dot(&ray->dir, &ray->dir);
	h = vec_dot(&ray->dir, &oc);
	c = vec_dot(&oc, &oc) - radius * radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	t1 = (h - sqrt_disc) / a;
	t2 = (h + sqrt_disc) / a;
	t_hit = t1 > 0.0001 ? t1 : (t2 > 0.0001 ? t2 : -1);
	if (t_hit < 0)
		return (false);
	hit->t = t_hit;
	hit->pos = ray_at(ray, t_hit);
	hit->normal = vec_sub(&hit->pos, &object->pos);
	hit->normal = vec_mul(&hit->normal, 1 / radius);
	hit->front_face = vec_dot(&ray->dir, &hit->normal) < 0;
	if (!hit->front_face)
		hit->normal = vec_mul(&hit->normal, -1);
	return (true);
}

bool	intersect(t_object *object, t_ray *ray, t_hit *hit)
{
	return (
		(object->type == SPHERE && inter_sphere(object, ray, hit))
		|| (object->type == PLANE && false)
		|| (object->type == CYLINDER && false)
		|| (object->type == CONE && false)
	);
}
