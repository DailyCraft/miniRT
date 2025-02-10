/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:29:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 15:58:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cylinder(t_element *element, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "cy", len, 6))
		return (false);
	element->type = CYLINDER;
	result = parse_vec(specs[1], &element->cylinder.pos, -FLT_MAX, FLT_MAX)
		&& parse_vec(specs[2], &element->cylinder.rot, -1, 1)
		&& parse_float(specs[3], &element->cylinder.diameter, 0, FLT_MAX)
		&& parse_float(specs[4], &element->cylinder.height, 0, FLT_MAX)
		&& parse_color(specs[5], &element->cylinder.color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_cone(t_element *element, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "co", len, 6))
		return (false);
	element->type = CONE;
	result = parse_vec(specs[1], &element->cone.pos, -FLT_MAX, FLT_MAX)
		&& parse_vec(specs[2], &element->cone.rot, -1, 1)
		&& parse_float(specs[3], &element->cone.base_width, 0, FLT_MAX)
		&& parse_float(specs[4], &element->cone.height, 0, FLT_MAX)
		&& parse_color(specs[5], &element->cone.color);
	if (result == 0)
		result = 2;
	return (result);
}
