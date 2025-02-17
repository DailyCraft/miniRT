/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:38:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 10:31:03 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parsing_is_type(char *type, char *name, size_t len, size_t required)
{
	static int	n = 0;

	if (ft_strcmp(type, name) != 0)
		return (false);
	n++;
	if (len != required)
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

// TODO: more secure
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

// TODO: more secure
// TODO: message when not in range
bool	parse_int(char *spec, int *value, int min, int max)
{
	*value = ft_atoi(spec);
	return (*value >= min && *value <= max);
}
