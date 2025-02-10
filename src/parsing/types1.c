/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:17:33 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 15:57:48 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_element *element, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "A", len, 3))
		return (0);
	element->type = AMBIENT;
	result = parse_float(specs[1], &element->ambient.ratio, 0, 1)
		&& parse_color(specs[2], &element->ambient.color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_camera(t_element *element, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "C", len, 4))
		return (false);
	element->type = CAMERA;
	result = parse_vec(specs[1], &element->camera.pos, -FLT_MAX, FLT_MAX)
		&& parse_vec(specs[2], &element->camera.rot, -1, 1)
		&& parse_float(specs[3], &element->camera.fov, 0, 180);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_light(t_element *element, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "L", len, 4))
		return (false);
	element->type = LIGHT;
	result = parse_vec(specs[1], &element->light.pos, -FLT_MAX, FLT_MAX)
		&& parse_float(specs[2], &element->light.brightness, 0, 1)
		&& parse_color(specs[3], &element->light.color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_sphere(t_element *element, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "sp", len, 4))
		return (false);
	element->type = SPHERE;
	result = parse_vec(specs[1], &element->sphere.pos, -FLT_MAX, FLT_MAX)
		&& parse_float(specs[2], &element->sphere.diameter, 0, FLT_MAX)
		&& parse_color(specs[3], &element->sphere.color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_plane(t_element *element, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "pl", len, 4))
		return (false);
	element->type = PLANE;
	result = parse_vec(specs[1], &element->plane.pos, -FLT_MAX, FLT_MAX)
		&& parse_vec(specs[2], &element->plane.rot, -1, 1)
		&& parse_color(specs[3], &element->sphere.color);
	if (result == 0)
		result = 2;
	return (result);
}
