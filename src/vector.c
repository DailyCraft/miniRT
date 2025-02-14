/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:24:58 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/14 12:58:18 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_magnitude(t_vec *vec)
{
	return (sqrtf(vec_dot(vec, vec)));
}

void	normalize(t_vec *vec)
{
	float	magnitude;

	magnitude = get_magnitude(vec);
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
}

float	distance(t_vec *pos1, t_vec *pos2)
{
	t_vec	sub;

	sub = vec_sub(pos2, pos1);
	return (get_magnitude(&sub));
}

inline t_vec	ray_at(t_ray *ray, float t)
{
	t_vec	vec;

	vec.x = ray->pos.x + t * ray->dir.x;
	vec.y = ray->pos.y + t * ray->dir.y;
	vec.z = ray->pos.z + t * ray->dir.z;
	return (vec);
}
