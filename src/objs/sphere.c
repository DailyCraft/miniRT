/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:48:22 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:48:52 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_uv(t_hit *hit)
{
	hit->u = atan2(hit->normal.x, hit->normal.z) / (2 * M_PI) + 0.5;
	hit->v = acos(hit->normal.y) / M_PI;
}
