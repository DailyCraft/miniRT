/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:27:26 by cgrasser          #+#    #+#             */
/*   Updated: 2025/02/27 21:34:53 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_determinant(t_vec ab, t_vec h, double *inv_det)
{
	double	determinant;

	determinant = vec_dot(ab, h);
	if (determinant > -0.0001 && determinant < 0.0001)
		return (false);
	*inv_det = 1.0 / determinant;
	return (true);
}

bool	check_ray_triangle_intersection(t_ray *ray, double inv_det,
	t_vec vecto[6], t_hit *hit)
{
	t_vec	s;
	t_vec	q;
	double	u;
	double	v;
	double	t;

	s = vec_sub(ray->pos, vecto[0]);
	u = vec_dot(s, vecto[5]) * inv_det;
	if (u < 0.0 || u > 1.0)
		return (false);
	q = vec_cross(&s, &vecto[3]);
	v = vec_dot(ray->dir, q) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return (false);
	t = vec_dot(vecto[4], q) * inv_det;
	if (t > 0.0001)
	{
		hit->pos = ray_at(ray, t);
		return (true);
	}
	return (false);
}

/*
	vecto[0] -> A
	vecto[1] -> B
	vecto[2] -> C
	vecto[3] -> AB
	vecto[4] -> AC
	vecto[5] -> pv ray->dir | AC
*/

bool	intersect_triangle(t_obj *obj, t_ray *ray, t_hit *hit)
{
	t_vec	vecto[6];
	double	inv_det;

	vecto[0] = obj->triangle.pos1;
	vecto[1] = obj->triangle.pos2;
	vecto[2] = obj->triangle.pos3;
	vecto[3] = vec_sub(vecto[1], vecto[0]);
	vecto[4] = vec_sub(vecto[2], vecto[0]);
	vecto[5] = vec_cross(&ray->dir, &vecto[4]);
	if (!check_determinant(vecto[3], vecto[5], &inv_det))
		return (false);
	if (!check_ray_triangle_intersection(ray, inv_det, vecto, hit))
		return (false);
	return (true);
}
