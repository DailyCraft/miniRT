/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:49:40 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:49:47 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	plane_uv(t_hit *hit)
{
	t_vec	u;
	t_vec	v;

	if (fabs(hit->normal.x) > fabs(hit->normal.y))
		u = (t_vec){-hit->normal.z, 0, hit->normal.x};
	else
		u = (t_vec){0, hit->normal.z, -hit->normal.y};
	normalize(&u);
	v = vec_cross(&hit->normal, &u);
	normalize(&v);
	hit->u = vec_dot(hit->pos, u) * 0.05;
	hit->v = vec_dot(hit->pos, v) * 0.05;
	hit->u -= floor(hit->u);
	hit->v -= floor(hit->v);
}
