/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:29:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/25 20:26:25 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//texture
bool	parse_cylinder(t_obj *object, char **specs, size_t len, bool *status)
{
	if (!parsing_is_type(specs[0], "cy", len, 6))
		return (false);
	object->type = CYLINDER;
	*status = parse_vec(specs[1], &object->pos, DBL_MAX, false)
		&& parse_vec(specs[2], &object->dir, 1, true)
		&& parse_double(specs[3], &object->cylinder.diameter, 0, DBL_MAX)
		&& parse_double(specs[4], &object->cylinder.height, 0, DBL_MAX)
		&& parse_texture(specs[5], object);
	if (len == 7)
		*status = *status && parse_bump(specs[6], &object->bump.image_path);
	object->has_bump = false;
	return (true);
}

bool	parse_triangle(t_obj *object, char **specs, size_t len, bool *status)
{
	if (!parsing_is_type(specs[0], "tr", len, 5))
		return (false);
	object->type = TRIANGLE;
	*status = parse_vec(specs[1], &object->triangle.pos1, DBL_MAX, false)
		&& parse_vec(specs[2], &object->triangle.pos2, DBL_MAX, false)
		&& parse_vec(specs[3], &object->triangle.pos3, DBL_MAX, false)
		&& parse_texture(specs[4], object);
	return (true);
}

bool	parse_cone(t_obj *object, char **specs, size_t len, bool *status)
{
	if (!parsing_is_type(specs[0], "co", len, 6))
		return (false);
	object->type = CONE;
	*status = parse_vec(specs[1], &object->pos, DBL_MAX, false)
		&& parse_vec(specs[2], &object->dir, 1, true)
		&& parse_double(specs[3], &object->cone.base_width, 0, DBL_MAX)
		&& parse_double(specs[4], &object->cone.height, 0, DBL_MAX)
		&& parse_texture(specs[5], object);
	return (true);
}
