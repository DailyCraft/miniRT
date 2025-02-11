/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:48:12 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/11 16:09:43 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	intersectSphere(t_sphere *sphere, t_vec *pos, t_vec *dir, t_vec *hit)
{
	t_vec oc = {pos->x - sphere->pos.x, pos->y - sphere->pos.y, pos->z - sphere->pos.z};
	double radius = sphere->diameter / 2.0;

	double a = dir->x * dir->x + dir->y * dir->y + dir->z * dir->z;
	double b = 2.0 * (oc.x * dir->x + oc.y * dir->y + oc.z * dir->z);
	double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - radius * radius;

	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (false);

	double sqrt_disc = sqrt(discriminant);
	double t1 = (-b - sqrt_disc) / (2.0 * a);
	double t2 = (-b + sqrt_disc) / (2.0 * a);

	// On prend le plus petit t positif
	double t_hit = (t1 > 0) ? t1 : (t2 > 0 ? t2 : -1);
	if (t_hit < 0)
		return (false);

	hit->x = pos->x + t_hit * dir->x;
	hit->y = pos->y + t_hit * dir->y;
	hit->z = pos->z + t_hit * dir->z;
	return (true);
}

int	intersect(t_element *element, t_vec *pos, t_vec *dir, t_vec *hit)
{
	if (element->type == SPHERE && intersectSphere(&element->sphere, pos, dir, hit))
		return (element->sphere.color);
	return (-1);
}
