/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:24:58 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 14:01:38 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline double	get_magnitude(t_vec *vec)
{
	return (sqrt(vec_dot(*vec, *vec)));
}

void	normalize(t_vec *vec)
{
	double	magnitude;

	magnitude = get_magnitude(vec);
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
}

double	distance(t_vec *pos1, t_vec *pos2)
{
	t_vec	sub;

	sub = vec_sub(*pos2, *pos1);
	return (get_magnitude(&sub));
}

inline t_vec	ray_at(t_ray *ray, double t)
{
	return ((t_vec){
		ray->pos.x + t * ray->dir.x,
		ray->pos.y + t * ray->dir.y,
		ray->pos.z + t * ray->dir.z
	});
}
