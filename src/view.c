/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:19:25 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 10:02:06 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sum_light(t_camera *camera, t_hit *hit, t_light *light,
	t_vec *brightness)
{
	t_vec	v;
	t_vec	l;
	t_vec	r;
	double	diffuse;
	double	specular;

	v = vec_sub(camera->pos, hit->pos);
	normalize(&v);
	l = vec_sub(light->pos, hit->pos);
	normalize(&l);
	r = vec_sub(vec_mul(&hit->normal, 2 * vec_dot(l, hit->normal)), l);
	normalize(&r);
	diffuse = light->brightness * fmax(vec_dot(l, hit->normal), 0);
	specular = light->brightness * pow(fmax(vec_dot(r, v), 0),
			hit->obj->shininess);
	brightness->x += light->color.r / 255 * (diffuse + specular);
	brightness->y += light->color.g / 255 * (diffuse + specular);
	brightness->z += light->color.b / 255 * (diffuse + specular);
}

static int	get_phong_color(t_data *data, t_camera *camera,
	t_obj *object, t_hit *hit)
{
	t_vec	brightness;
	t_list	*lst;
	t_light	*light;
	t_ray	ray;
	t_color	color;

	brightness.x = data->ambient->color.r / 255 * data->ambient->brightness;
	brightness.y = data->ambient->color.g / 255 * data->ambient->brightness;
	brightness.z = data->ambient->color.b / 255 * data->ambient->brightness;
	lst = data->lights;
	while (lst)
	{
		light = lst->content;
		ray.pos = hit->pos;
		ray.dir = vec_sub(light->pos, hit->pos);
		normalize(&ray.dir);
		if (!get_object(data, &ray, NULL, distance(&hit->pos, &light->pos)))
			sum_light(camera, hit, light, &brightness);
		lst = lst->next;
	}
	get_pixel_color(data, object, hit, &color);
	return (ft_rgb(
			fmin(color.r * brightness.x, 255),
			fmin(color.g * brightness.y, 255),
			fmin(color.b * brightness.z, 255)));
}

static int	get_ray_color(t_data *data, t_camera *camera, int x, int y)
{
	t_obj	*object;
	t_ray	ray;
	t_hit	hit;

	ray = gen_ray(camera, x, y);
	object = get_object(data, &ray, &hit, DBL_MAX);
	if (object)
		return (get_phong_color(data, camera, object, &hit));
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
				= get_ray_color(data, camera, x, y);
			x++;
		}
		if (y % (HEIGHT / 20) == 0)
			printf("%3.f %%\n", (float) y / HEIGHT * 100);
		y++;
	}
	printf("%3.f %%\n", (float) y / HEIGHT * 100);
}
