/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:24:58 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/12 15:59:49 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_vec	vec_sub(t_vec *a, t_vec *b)
{
	t_vec	vec;

	vec.x = a->x - b->x;
	vec.y = a->y - b->y;
	vec.z = a->z - b->z;
	return (vec);
}

inline float	vec_dot(t_vec *a, t_vec *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

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
