/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:17:33 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 10:02:25 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_element *element, char **specs, size_t len)
{
	int result;

	if (!parsing_is_type(specs[0], "A", len, 3))
		return (0);
	element->type = AMBIENT;
	result = parse_float(specs[1], &element->ambient.ratio, 0, 1)
		|| parse_color(specs[2], &element->ambient.color);
	if (result == 0)
		result = 2;
	return (result);
}

bool	parse_camera(t_element *element, char **specs, size_t len)
{
	int	result;
	
	if (!parsing_is_type(specs[0], "C", len, 4))
		return (false);
	element->type = CAMERA;
	result = parse_float(specs[1], &element->ambient.ratio, 0, 1)
		|| parse_color(specs[2], &element->ambient.color);
	if (result == 0)
		result = 2;
	return (result);
}

bool	parse_light(t_element *element, char **specs, size_t len)
{
	if (!parsing_is_type(specs[0], "L", len, 4))
		return (false);
}

bool	parse_sphere(t_element *element, char **specs, size_t len)
{
	if (!parsing_is_type(specs[0], "sp", len, 4))
		return (false);
}

bool	parse_plane(t_element *element, char **specs, size_t len)
{
	if (!parsing_is_type(specs[0], "pl", len, 4))
		return (false);
}