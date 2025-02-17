/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:17:33 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 10:35:50 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_data *data, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "A", len, 3))
		return (0);
	if (data->ambient)
	{
		printf("Multiple ambient light is unallowed!\n");
		return (2);
	}
	data->ambient = malloc(sizeof(t_ambient));
	result = parse_double(specs[1], &data->ambient->brightness, 0, 1)
		&& parse_color(specs[2], &data->ambient->color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_camera(t_data *data, char **specs, size_t len)
{
	int			result;
	t_camera	*camera;

	if (!parsing_is_type(specs[0], "C", len, 4))
		return (false);
	camera = malloc(sizeof(t_camera));
	camera->image = NULL;
	ft_lstadd_back(&data->cameras, ft_lstnew(camera));
	result = parse_vec(specs[1], &camera->pos, DBL_MAX, false)
		&& parse_vec(specs[2], &camera->rot, 1, true)
		&& parse_double(specs[3], &camera->fov, 0, 180);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_light(t_data *data, char **specs, size_t len)
{
	int		result;
	t_light	*light;

	if (!parsing_is_type(specs[0], "L", len, 4))
		return (false);
	light = malloc(sizeof(t_light));
	ft_lstadd_back(&data->lights, ft_lstnew(light));
	result = parse_vec(specs[1], &light->pos, DBL_MAX, false)
		&& parse_double(specs[2], &light->brightness, 0, 1)
		&& parse_color(specs[3], &light->color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_sphere(t_object *object, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "sp", len, 4))
		return (false);
	object->type = SPHERE;
	result = parse_vec(specs[1], &object->pos, DBL_MAX, false)
		&& parse_double(specs[2], &object->sphere.diameter, 0, DBL_MAX)
		&& parse_color(specs[3], &object->color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_plane(t_object *object, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "pl", len, 4))
		return (false);
	object->type = PLANE;
	result = parse_vec(specs[1], &object->pos, DBL_MAX, false)
		&& parse_vec(specs[2], &object->rot, 1, true)
		&& parse_color(specs[3], &object->color);
	if (result == 0)
		result = 2;
	return (result);
}
