/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:24:58 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/11 16:13:15 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize(t_vec *vec)
{
	float	magnitude;

	magnitude = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
}

void	rotate_axis(float *vec1, float *vec2, float axis)
{
	float	cos_axis;
	float	sin_axis;
	float	o1;
	float	o2;

	cos_axis = cos(axis);
	sin_axis = sin(axis);
	o1 = *vec1;
	o2 = *vec2;
	*vec1 = o1 * cos_axis - o2 * sin_axis;
	*vec2 = o1 * sin_axis + o2 * cos_axis;
}

float distance(t_vec *pos1, t_vec *pos2)
{
	double	x;
	double	y;
	double	z;

	x = pos2->x - pos1->x;
	y = pos2->y - pos1->y;
	z = pos2->z - pos1->z;
	return (sqrt(x * x + y * y + z * z));
}