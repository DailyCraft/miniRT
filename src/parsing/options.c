/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:42:01 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 11:57:07 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	bump(t_obj *obj, char *spec)
{
	bool	result;

	if (obj->has_bump)
	{
		printf("Bump map option set multiple times.");
		return (false);
	}
	obj->has_bump = true;
	result = parse_texture(spec, &obj->bump);
	if (result && obj->bump.image_path == NULL)
	{
		printf("Invalid bump map.\n");
		return (false);
	}
	return (true);
}

static bool	checkerboard(t_obj *obj, char *spec)
{
	if (obj->has_checkerboard)
	{
		printf("Checkerboard option set multiple times.");
		return (false);
	}
	obj->has_checkerboard = true;
	return (parse_texture(spec, &obj->checkerboard));
}

static bool	shininess(t_obj *obj, char *spec)
{
	return (parse_double(spec, &obj->shininess, 0, 500));
}

bool	parse_option(t_obj *obj, char *spec)
{
	if (ft_strncmp(spec, "--bump=", 7) == 0)
		return (bump(obj, spec + 7));
	if (ft_strncmp(spec, "-b=", 3) == 0)
		return (bump(obj, spec + 3));
	if (ft_strncmp(spec, "--checkerboard=", 15) == 0)
		return (checkerboard(obj, spec + 15));
	if (ft_strncmp(spec, "-c=", 3) == 0)
		return (checkerboard(obj, spec + 3));
	if (ft_strncmp(spec, "--shininess=", 12) == 0)
		return (shininess(obj, spec + 12));
	if (ft_strncmp(spec, "-s=", 3) == 0)
		return (shininess(obj, spec + 3));
	printf("Unknown option: %s\n", spec);
	return (false);
}
