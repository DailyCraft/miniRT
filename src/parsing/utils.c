/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:38:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/25 20:43:57 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TODO: Cameras and lights don't have bump texture
bool	parsing_is_type(char *type, char *name, size_t len, size_t required)
{
	static int	n = 0;

	if (ft_strcmp(type, name) != 0)
		return (false);
	n++;
	if (len != required && len != required + 1)
	{
		printf("Incorrect element n.%d specs length."
			" Required: %ld, current: %ld\n",
			n, required, len);
		return (false);
	}
	return (true);
}

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

// TODO: more secure / check if texture existe ?
bool	parse_texture(char *spec, t_obj *object)
{
	if (ft_strncmp(spec, "tx:", 3) == 0)
	{
		object->texture.is_color = false;
		object->texture.image_path = ft_strdup(spec + 3);
	}
	else
	{
		object->texture.is_color = true;
		return (parse_color(spec, &object->texture.color));
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

// TODO: more secure
// TODO: message when not in range
bool	parse_double(char *spec, double *value, double min, double max)
{
	*value = ft_atof(spec);
	return (*value >= min && *value <= max);
}

bool	parse_bump(char *spec, char **path)
{
	if (access(spec, R_OK) == -1)
	{
		perror(spec);
		errno = 0;
		return (false);
	}
	*path = ft_strdup(spec);
	return (true);
}
