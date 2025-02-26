/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:17:33 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:45:15 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	is_type(char *type, char *name, size_t len, size_t required)
{
	if (ft_strcmp(type, name) != 0)
		return (false);
	if (len != required)
	{
		printf("Incorrect specs length.\n");
		return (false);
	}
	return (true);
}

bool	parse_ambient(t_data *data, char **specs, size_t len, bool *status)
{
	if (!is_type(specs[0], "A", len, 3))
		return (false);
	if (data->ambient)
	{
		printf("Multiple ambient light is not allowed!\n");
		return (2);
	}
	data->ambient = malloc(sizeof(t_ambient));
	*status = parse_double(specs[1], &data->ambient->brightness, 0, 1)
		&& parse_color(specs[2], &data->ambient->color);
	return (true);
}

bool	parse_camera(t_data *data, char **specs, size_t len, bool *status)
{
	t_camera	*camera;

	if (!is_type(specs[0], "C", len, 4))
		return (false);
	camera = malloc(sizeof(t_camera));
	camera->image = NULL;
	ft_lstadd_back(&data->cameras, ft_lstnew(camera));
	*status = parse_vec(specs[1], &camera->pos, DBL_MAX, false)
		&& parse_vec(specs[2], &camera->dir, 1, true)
		&& parse_double(specs[3], &camera->fov, 0, 180);
	return (true);
}

bool	parse_light(t_data *data, char **specs, size_t len, bool *status)
{
	t_light	*light;

	if (!is_type(specs[0], "L", len, 4))
		return (false);
	light = malloc(sizeof(t_light));
	ft_lstadd_back(&data->lights, ft_lstnew(light));
	*status = parse_vec(specs[1], &light->pos, DBL_MAX, false)
		&& parse_double(specs[2], &light->brightness, 0, 1)
		&& parse_color(specs[3], &light->color);
	return (true);
}
