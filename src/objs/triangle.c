/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:27:26 by cgrasser          #+#    #+#             */
/*   Updated: 2025/02/28 11:23:44 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_inter(t_ray *ray, double inv_det, t_vec vecto[6], t_hit *hit)
{
	t_vec	s;
	t_vec	q;
	double	u;
	double	v;
	double	t;

	s = vec_sub(ray->pos, vecto[0]);
	u = vec_dot(s, vecto[5]) * inv_det;
	if (u < 0 || u > 1)
		return (false);
	q = vec_cross(s, vecto[3]);
	v = vec_dot(ray->dir, q) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return (false);
	t = vec_dot(vecto[4], q) * inv_det;
	if (t > 0.0001)
	{
		hit->pos = ray_at(ray, t);
		hit->normal = vec_cross(vecto[3], vecto[4]);
		if (vec_dot(ray->dir, hit->normal) > 0)
			hit->normal = vec_mul(hit->normal, -1);
		normalize(&hit->normal);
		return (true);
	}
	return (false);
}

/**
 * vecto[0] -> A
 * vecto[1] -> B
 * vecto[2] -> C
 * vecto[3] -> AB
 * vecto[4] -> AC
 * vecto[5] -> pv ray->dir | AC
 */
bool	inter_triangle(t_obj *obj, t_ray *ray, t_hit *hit)
{
	t_vec	vecto[6];
	double	inv_det;

	vecto[0] = obj->triangle.pos1;
	vecto[1] = obj->triangle.pos2;
	vecto[2] = obj->triangle.pos3;
	vecto[3] = vec_sub(vecto[1], vecto[0]);
	vecto[4] = vec_sub(vecto[2], vecto[0]);
	vecto[5] = vec_cross(ray->dir, vecto[4]);
	inv_det = vec_dot(vecto[3], vecto[5]);
	if (fabs(inv_det) < 0.0001)
		return (false);
	inv_det = 1 / inv_det;
	return (check_inter(ray, inv_det, vecto, hit));
}

void	triangle_uv(t_hit *hit)
{
	(void) hit;
}
