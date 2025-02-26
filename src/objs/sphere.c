/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:48:22 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 16:15:17 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	inter_sphere(t_obj *object, t_ray *ray, t_hit *hit)
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

void	sphere_uv(t_hit *hit)
{
	hit->u = atan2(hit->normal.x, hit->normal.z) / (2 * M_PI) + 0.5;
	hit->v = acos(hit->normal.y) / M_PI;
}
