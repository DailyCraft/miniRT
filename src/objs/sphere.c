/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:48:22 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/28 11:30:53 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	inter_sphere(t_obj *object, t_ray *ray, t_hit *hit)
{
	t_vec	oc;
	double	a;
	double	h;
	double	t_hit;

	oc = vec_sub(object->pos, ray->pos);
	a = vec_dot(ray->dir, ray->dir);
	h = vec_dot(ray->dir, oc);
	t_hit = compute_hit_point(a, h, &oc, object->sphere.diameter);
	if (t_hit == -1)
		return (false);
	hit->pos = ray_at(ray, t_hit);
	hit->normal = vec_sub(hit->pos, object->pos);
	normalize(&hit->normal);
	return (true);
}

void	sphere_uv(t_hit *hit)
{
	hit->u = atan2(hit->normal.z, hit->normal.x) / (2 * M_PI);
	hit->v = acos(hit->normal.y) / M_PI;
}
