/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:19:25 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/12 16:17:00 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	*get_object(t_data *data, t_vec *pos, t_vec *dir, t_vec *hit)
{
	float		min_dist;
	t_object	*object;
	t_list		*lst;

	min_dist = FLT_MAX;
	object = NULL;
	lst = data->objects;
	while (lst)
	{
		if (intersect(lst->content, pos, dir, hit)
			&& distance(pos, hit) < min_dist)
		{
			min_dist = distance(pos, hit);
			object = lst->content;
		}
		lst = lst->next;
	}
	return (object);
}

// TODO: Colored light
static int	get_object_color(t_data *data, t_object *object, t_vec *hit)
{
	float	brightness;
	t_list	*lst;
	t_light	*light;
	t_vec	dir;
	t_vec	temp;

	brightness = data->ambient->brightness;
	lst = data->lights;
	while (lst)
	{
		light = lst->content;
		dir.x = light->pos.x - hit->x;
		dir.y = light->pos.y - hit->y;
		dir.z = light->pos.z - hit->z;
		if (!get_object(data, hit, &dir, &temp))
			brightness += light->brightness;
		lst = lst->next;
	}
	return (ft_rgb(object->color.r * brightness, object->color.g * brightness,
			object->color.b * brightness));
}

// TODO: camera to world
static int	get_pixel_color(t_data *data, t_camera *camera, int x, int y)
{
	t_vec		vec;
	float		scale;
	t_object	*object;
	t_vec		hit;

	scale = tan(camera->fov * M_PI / 180 / 2);
	vec.x = (2 * (x + 0.5) / WIDTH - 1) * scale * (WIDTH / HEIGHT);
	vec.y = (1 - 2 * (y + 0.5) / HEIGHT) * scale;
	vec.z = -1;
	normalize(&vec);
	object = get_object(data, &camera->pos, &vec, &hit);
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
