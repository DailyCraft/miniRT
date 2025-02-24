/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:54 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/24 16:13:47 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TODO: camera to world
t_ray	gen_ray(t_camera *camera, int x, int y)
{
	t_ray	ray;
	double	scale;

	ray.pos = camera->pos;
	scale = tan(camera->fov * M_PI / 180 / 2);
	ray.dir.x = (2 * (x + 0.5) / WIDTH - 1) * scale * (WIDTH / HEIGHT);
	ray.dir.y = (1 - 2 * (y + 0.5) / HEIGHT) * scale;
	ray.dir.z = -1;
	normalize(&ray.dir);
	return (ray);
}

t_obj	*get_object(t_data *data, t_ray *ray, t_hit *hit, double max)
{
	double	dist;
	double	min_dist;
	t_obj	*object;
	t_hit	temp;
	t_list	*lst;

	min_dist = max;
	object = NULL;
	lst = data->objects;
	while (lst)
	{
		if (intersect(lst->content, ray, &temp))
		{
			dist = distance(&ray->pos, &temp.pos);
			if (dist < min_dist)
			{
				min_dist = dist;
				object = lst->content;
				*hit = temp;
			}
		}
		lst = lst->next;
	}
	return (object);
}
