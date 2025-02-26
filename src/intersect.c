/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:48:12 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 17:03:02 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	calculate_hit_point(double *hit, double disc, double h, double a)
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

bool	intersect(t_obj *object, t_ray *ray, t_hit *hit)
{
	hit->obj = object;
	return (
		(object->type == SPHERE && inter_sphere(object, ray, hit))
		|| (object->type == PLANE && inter_plane(object, ray, hit))
		|| (object->type == CYLINDER && inter_cylinder(object, ray, hit))
		|| (object->type == TRIANGLE && intersect_triangle(object, ray, hit))
		|| (object->type == CONE && false)
	);
}
