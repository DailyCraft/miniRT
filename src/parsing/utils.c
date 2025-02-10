/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:38:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 15:51:09 by dvan-hum         ###   ########.fr       */
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
bool	parse_vec(char *spec, t_vec *vec, float min, float max)
{
	vec->x = ft_atoi(spec);
	spec = ft_strchr(spec, ',');
	if (!spec || vec->x < min || vec->x > max)
		return (false);
	vec->y = ft_atoi(spec);
	spec = ft_strchr(spec, ',');
	if (!spec || vec->y < min || vec->y > max)
		return (false);
	vec->z = ft_atoi(spec);
	return (vec->z >= min && vec->z <= max);
}

// TODO: more secure
bool	parse_color(char *spec, int *color)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(spec);
	spec = ft_strchr(spec, ',');
	if (!spec || r < 0 || r > 255)
		return (false);
	g = ft_atoi(spec);
	spec = ft_strchr(spec, ',');
	if (!spec || g < 0 || g > 255)
		return (false);
	b = ft_atoi(spec);
	*color = ft_rgb(r, g, b);
	return (b >= 0 && b <= 255);
}

// TODO: more secure
// TODO: message when not in range
bool	parse_float(char *spec, float *value, float min, float max)
{
	*value = (float) ft_atof(spec);
	return (*value >= min && *value <= max);
}

// TODO: more secure
// TODO: message when not in range
bool	parse_int(char *spec, int *value, int min, int max)
{
	*value = ft_atoi(spec);
	return (*value >= min && *value <= max);
}
