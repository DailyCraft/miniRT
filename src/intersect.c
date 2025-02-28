/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:48:12 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/28 08:59:39 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	compute_hit_point(double a, double h, t_vec *oc, double diameter)
{
	double	sqrt_disc;
	double	t1;
	double	t2;

	sqrt_disc = sqrt(h * h - a * (vec_dot(*oc, *oc) - diameter * diameter / 4));
	t1 = (h - sqrt_disc) / a;
	t2 = (h + sqrt_disc) / a;
	if (t1 > 0.0001)
		return (t1);
	else if (t2 > 0.0001)
		return (t2);
	return (-1);
}

bool	intersect(t_obj *object, t_ray *ray, t_hit *hit)
{
	hit->obj = object;
	return (
		(object->type == SPHERE && inter_sphere(object, ray, hit))
		|| (object->type == PLANE && inter_plane(object, ray, hit))
		|| (object->type == CYLINDER && inter_cylinder(object, ray, hit))
		|| (object->type == TRIANGLE && inter_triangle(object, ray, hit))
		|| (object->type == CONE && false)
	);
}
