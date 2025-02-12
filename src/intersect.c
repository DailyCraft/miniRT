/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:48:12 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/12 16:24:06 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	inter_sphere(t_object *object, t_vec *pos, t_vec *dir, t_vec *hit)
{
	t_vec	oc;
	float	radius;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	t_hit;

	oc = vec_sub(&object->pos, pos);
	radius = object->sphere.diameter / 2.0;
	a = vec_dot(dir, dir);
	b = -2.0 * vec_dot(dir, &oc);
	c = vec_dot(&oc, &oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	t1 = (-b - sqrt_disc) / (2.0 * a);
	t2 = (-b + sqrt_disc) / (2.0 * a);
	t_hit = t1 > 0 ? t1 : (t2 > 0 ? t2 : -1);
	if (t_hit < 0)
		return (false);
	hit->x = pos->x + t_hit * dir->x;
	hit->y = pos->y + t_hit * dir->y;
	hit->z = pos->z + t_hit * dir->z;
	return (true);
}

bool	intersect(t_object *object, t_vec *pos, t_vec *dir, t_vec *hit)
{
	return (
		(object->type == SPHERE && inter_sphere(object, pos, dir, hit))
		|| (object->type == PLANE && false)
		|| (object->type == CYLINDER && false)
		|| (object->type == CONE && false)
	);
}
