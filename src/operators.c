/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:58:20 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/23 18:13:29 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_vec	vec_add(t_vec *u, t_vec *v)
{
	t_vec	vec;

	vec.x = u->x + v->x;
	vec.y = u->y + v->y;
	vec.z = u->z + v->z;
	return (vec);
}

inline t_vec	vec_sub(t_vec u, t_vec v)
{
	t_vec	vec;

	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	vec.z = u.z - v.z;
	return (vec);
}

inline double	vec_dot(t_vec u, t_vec v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

inline t_vec	vec_cross(t_vec *u, t_vec *v)
{
	t_vec	vec;

	vec.x = u->y * v->z - u->z * v->y;
	vec.y = u->z * v->x - u->x * v->z;
	vec.z = u->x * v->y - u->y * v->x;
	return (vec);
}

inline t_vec	vec_mul(t_vec *v, double f)
{
	t_vec	vec;

	vec.x = v->x * f;
	vec.y = v->y * f;
	vec.z = v->z * f;
	return (vec);
}
