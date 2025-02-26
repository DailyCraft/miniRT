/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:49:04 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:49:20 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cylinder_uv(t_data *data, t_obj *object, t_hit *hit)
{
	t_vec	v;
	t_vec	cam;
	t_vec	temp;

	v = vec_sub(object->pos, hit->pos);
	cam = ((t_camera *) data->cameras->content)->dir;
	temp = vec_cross(&object->dir, &cam);
	hit->u = atan2(vec_dot(vec_cross(&object->dir, &cam), v),
			vec_dot(vec_cross(&temp, &object->dir), v)) / (2 * M_PI) + 0.5;
	hit->v = vec_dot(object->dir, v) / object->cylinder.height + 1;
}
