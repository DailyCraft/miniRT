/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:58:20 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/27 19:53:01 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_vec	vec_add(t_vec *u, t_vec *v)
{
	return ((t_vec){
		u->x + v->x,
		u->y + v->y,
		u->z + v->z
	});
}

inline t_vec	vec_sub(t_vec u, t_vec v)
{
	return ((t_vec){
		u.x - v.x,
		u.y - v.y,
		u.z - v.z
	});
}

inline double	vec_dot(t_vec u, t_vec v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

inline t_vec	vec_cross(t_vec *u, t_vec *v)
{
	return ((t_vec){
		u->y * v->z - u->z * v->y,
		u->z * v->x - u->x * v->z,
		u->x * v->y - u->y * v->x
	});
}

inline t_vec	vec_mul(t_vec *v, double f)
{
	return ((t_vec){
		v->x * f,
		v->y * f,
		v->z * f
	});
}
