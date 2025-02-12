/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:29:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/12 09:58:38 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cylinder(t_object *object, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "cy", len, 6))
		return (false);
	object->type = CYLINDER;
	result = parse_vec(specs[1], &object->pos, FLT_MAX, false)
		&& parse_vec(specs[2], &object->rot, 1, true)
		&& parse_float(specs[3], &object->cylinder.diameter, 0, FLT_MAX)
		&& parse_float(specs[4], &object->cylinder.height, 0, FLT_MAX)
		&& parse_color(specs[5], &object->color);
	if (result == 0)
		result = 2;
	return (result);
}

int	parse_cone(t_object *object, char **specs, size_t len)
{
	int	result;

	if (!parsing_is_type(specs[0], "co", len, 6))
		return (false);
	object->type = CONE;
	result = parse_vec(specs[1], &object->pos, FLT_MAX, false)
		&& parse_vec(specs[2], &object->rot, 1, true)
		&& parse_float(specs[3], &object->cone.base_width, 0, FLT_MAX)
		&& parse_float(specs[4], &object->cone.height, 0, FLT_MAX)
		&& parse_color(specs[5], &object->color);
	if (result == 0)
		result = 2;
	return (result);
}
