/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:46:13 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:46:44 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TODO: more secure
// TODO: message when not in range
bool	parse_vec(char *spec, t_vec *vec, double limit, bool normalized)
{
	char	*str;

	str = spec;
	vec->x = ft_atof(str);
	str = ft_strchr(str, ',');
	if (!str || vec->x < -limit || vec->x > limit)
		return (false);
	vec->y = ft_atof(str + 1);
	str = ft_strchr(str + 1, ',');
	if (!str || vec->y < -limit || vec->y > limit)
		return (false);
	vec->z = ft_atof(str + 1);
	if (vec->z < -limit && vec->z > limit)
		return (false);
	if (normalized && get_magnitude(vec) != 1)
	{
		printf("The vector %s is not normilized! Normilizing it...\n", spec);
		if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		{
			printf("The zero vector cannot be normilized!\n");
			return (false);
		}
		normalize(vec);
	}
	return (true);
}

bool	parse_color(char *spec, t_color *color)
{
	color->r = ft_atoi(spec);
	spec = ft_strchr(spec, ',');
	if (!spec)
		return (false);
	color->g = ft_atoi(spec + 1);
	spec = ft_strchr(spec + 1, ',');
	if (!spec)
		return (false);
	color->b = ft_atoi(spec + 1);
	return (true);
}

bool	parse_texture(char *spec, t_texture *texture)
{
	if (ft_strchr(spec, '/') == NULL)
		return (parse_color(spec, &texture->color));
	if (access(spec, R_OK) == -1)
	{
		perror(spec);
		errno = 0;
		return (false);
	}
	texture->image_path = ft_strdup(spec);
	return (true);
}

// TODO: more secure
// TODO: message when not in range
bool	parse_double(char *spec, double *value, double min, double max)
{
	*value = ft_atof(spec);
	return (*value >= min && *value <= max);
}
