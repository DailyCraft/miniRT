/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:19:25 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 10:36:53 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	*get_object(t_data *data, t_ray *ray, t_hit *hit, double max)
{
	double		min_dist;
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

static void	sum_light(t_camera *camera, t_hit *hit, t_light *light,
	t_vec *brightness)
{
	t_vec	v;
	t_vec	l;
	t_vec	r;
	double	diffuse;
	double	specular;

	v = vec_sub(&camera->pos, &hit->pos);
	normalize(&v);
	l = vec_sub(&light->pos, &hit->pos);
	normalize(&l);
	r = vec_mul(&hit->normal, 2 * vec_dot(&l, &hit->normal));
	r = vec_sub(&r, &l);
	normalize(&r);
	diffuse = light->brightness * fmax(vec_dot(&l, &hit->normal), 0);
	specular = light->brightness * pow(fmax(vec_dot(&r, &v), 0), 100);
	brightness->x += light->color.r / 255 * (diffuse + specular);
	brightness->y += light->color.g / 255 * (diffuse + specular);
	brightness->z += light->color.b / 255 * (diffuse + specular);
}

static int	get_object_color(t_data *data, t_camera *camera,
	t_object *object, t_hit *hit)
{
	t_vec	brightness;
	t_list	*lst;
	t_light	*light;
	t_ray	ray;
	t_hit	temp;

	brightness.x = data->ambient->color.r / 255 * data->ambient->brightness;
	brightness.y = data->ambient->color.g / 255 * data->ambient->brightness;
	brightness.z = data->ambient->color.b / 255 * data->ambient->brightness;
	lst = data->lights;
	while (lst)
	{
		light = lst->content;
		ray.pos = hit->pos;
		ray.dir = vec_sub(&light->pos, &hit->pos);
		normalize(&ray.dir);
		if (!get_object(data, &ray, &temp, distance(&hit->pos, &light->pos)))
			sum_light(camera, hit, light, &brightness);
		lst = lst->next;
	}
	return (ft_rgb(
			fmin(object->color.r * brightness.x, 255),
			fmin(object->color.g * brightness.y, 255),
			fmin(object->color.b * brightness.z, 255)
		));
}

// TODO: camera to world
static int	get_pixel_color(t_data *data, t_camera *camera, int x, int y)
{
	t_vec		vec;
	double		scale;
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
	object = get_object(data, &ray, &hit, DBL_MAX);
	if (object)
		return (get_object_color(data, camera, object, &hit));
	return (0);
}

void	update_image(t_data *data, t_camera *camera)
{
	int	x;
	int	y;

	if (camera->image)
		return ;
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
