/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:38:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:46:39 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_type(t_obj *obj, char *spec, size_t len)
{
	const char	*types[] = {"sp", "pl", "cy", "tr", "co", NULL};
	int			i;

	i = 0;
	while (types[i])
	{
		if (ft_strcmp(spec, types[i]) == 0)
		{
			obj->type = i;
			if (!((i < 2 && len >= 4) || (i == 3 && len >= 5) || len >= 6))
			{
				printf("Not enough specs.\n");
				return (false);
			}
			return (true);
		}
		i++;
	}
	printf("Unknown element identifier.\n");
	return (false);
}

bool	parse_extra(t_obj *obj, char **specs, int *i)
{
	if (obj->type == SPHERE)
		return (parse_double(specs[(*i)++], &obj->sphere.diameter, 0, DBL_MAX));
	else if (obj->type == CYLINDER)
		return (parse_double(specs[(*i)++], &obj->cylinder.diameter, 0, DBL_MAX)
			&& parse_double(specs[(*i)++], &obj->cylinder.height, 0, DBL_MAX));
	else if (obj->type == TRIANGLE)
		return (parse_vec(specs[(*i)++], &obj->triangle.pos1, DBL_MAX, false)
			&& parse_vec(specs[(*i)++], &obj->triangle.pos2, DBL_MAX, false)
			&& parse_vec(specs[(*i)++], &obj->triangle.pos3, DBL_MAX, false));
	else if (obj->type == CONE)
		return (parse_double(specs[(*i)++], &obj->cone.base_width, 0, DBL_MAX)
			&& parse_double(specs[(*i)++], &obj->cone.height, 0, DBL_MAX));
	return (true);
}
