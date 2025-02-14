/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:19:25 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/14 16:08:16 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	*get_object(t_data *data, t_ray *ray, t_hit *hit, float max)
{
	float		min_dist;
	t_object	*object;
	t_list		*lst;

	min_dist = max;
	object = NULL;
	lst = data->objects;
	while (lst)
	{
		if (intersect(lst->content, ray, hit)
			&& distance(&ray->pos, &hit->pos) < min_dist)
		{
			min_dist = distance(&ray->pos, &hit->pos);
			object = lst->content;
		}
		lst = lst->next;
	}
	return (object);
}

// TODO: Colored light
static int	get_object_color(t_data *data, t_object *object, t_hit *hit)
{
	t_color	color;
	float	brightness;
	t_list	*lst;
	t_light	*light;
	t_ray	ray;
	t_hit	temp;

	brightness = data->ambient->brightness;
	color.r = data->ambient->color.r * brightness;
	color.g = data->ambient->color.g * brightness;
	color.b = data->ambient->color.b * brightness;
	lst = data->lights;
	while (lst)
	{
		light = lst->content;
		ray.pos = hit->pos;
		ray.dir = vec_sub(&light->pos, &hit->pos);
		float dist = distance(&hit->pos, &light->pos);
		if (!get_object(data, &ray, &temp, dist))
		{
			float light_brightness = light->brightness * 20 / (dist * dist) * fmax(0, vec_dot(&ray.dir, &hit->normal));
			brightness += light_brightness;
			color.r += light->color.r * light_brightness;
			color.g += light->color.g * light_brightness;
			color.b += light->color.b * light_brightness;
		}
		lst = lst->next;
	}
	color.r += object->color.r * brightness;
	color.g += object->color.g * brightness;
	color.b += object->color.b * brightness;
	color.r = fmin(255, color.r);
	color.g = fmin(255, color.g);
	color.b = fmin(255, color.b);
	return (color.color);
}

// TODO: camera to world
static int	get_pixel_color(t_data *data, t_camera *camera, int x, int y)
{
	t_vec		vec;
	float		scale;
	t_object	*object;
	t_ray		ray;
	t_hit		hit;

	scale = tan(camera->fov * M_PI / 180 / 2);
	vec.x = (2 * (x + 0.5) / WIDTH - 1) * scale * (WIDTH / HEIGHT);
	vec.y = (1 - 2 * (y + 0.5) / HEIGHT) * scale;
	vec.z = -1;
	normalize(&vec);
	ray.pos = camera->pos;
	ray.dir = vec;
	object = get_object(data, &ray, &hit, FLT_MAX);
	if (object)
		return (get_object_color(data, object, &hit));
	return (0);
}

void	update_image(t_data *data, t_camera *camera)
{
	int	x;
	int	y;

	if (!camera->image)
		camera->image = mlx_create_image(data);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			camera->image->data[y * WIDTH + x]
				= get_pixel_color(data, camera, x, y);
			x++;
		}
		y++;
	}
}
