/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:49:40 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/28 10:42:04 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	inter_plane(t_obj *object, t_ray *ray, t_hit *hit)
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
	hit->normal = object->dir;
	if (denom > 0)
		hit->normal = vec_mul(hit->normal, -1);
	normalize(&hit->normal);
	return (true);
}

void	plane_uv(t_hit *hit)
{
	t_vec	u;
	t_vec	v;

	if (fabs(hit->normal.x) > fabs(hit->normal.y))
		u = (t_vec){-hit->normal.z, 0, hit->normal.x};
	else
		u = (t_vec){0, hit->normal.z, -hit->normal.y};
	normalize(&u);
	v = vec_cross(hit->normal, u);
	normalize(&v);
	hit->u = vec_dot(hit->pos, u) * 0.05;
	hit->v = vec_dot(hit->pos, v) * 0.05;
	hit->u -= floor(hit->u);
	hit->v -= floor(hit->v);
}
