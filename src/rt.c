/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:54 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/28 11:15:35 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	gen_ray(t_camera *camera, int x, int y)
{
	t_ray	ray;
	double	scale;
	t_vec	cup;
	t_vec	right;
	t_vec	up;

	ray.pos = camera->pos;
	scale = tan(camera->fov * M_PI / 180 / 2);
	ray.dir.x = (2 * (x + 0.5) / WIDTH - 1) * scale * (WIDTH / HEIGHT);
	ray.dir.y = -(1 - 2 * (y + 0.5) / HEIGHT) * scale;
	ray.dir.z = -1;
	if (camera->dir.x != 0 || fabs(camera->dir.y) != 1 || camera->dir.z != 0)
		cup = (t_vec){0, 1, 0};
	else
		cup = (t_vec){0, 0, 1};
	right = vec_cross(camera->dir, cup);
	normalize(&right);
	up = vec_cross(right, camera->dir);
	ray.dir = vec_add(vec_mul(camera->dir, -ray.dir.z),
			vec_add(vec_mul(right, -ray.dir.x), vec_mul(up, -ray.dir.y)));
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
				if (hit)
					*hit = temp;
			}
		}
		lst = lst->next;
	}
	return (object);
}
