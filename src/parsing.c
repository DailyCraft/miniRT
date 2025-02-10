/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:24:48 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 09:59:11 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_elem(char *line, t_element **element)
{
	char		**specs;
	size_t		len;
	int			result;

	*element = ft_calloc(1, sizeof(t_element));
	specs = ft_split(line, " \t\n\v\f\r");
	len = 0;
	while (specs[len])
		len++;
	if (len == 0)
		result = 1;
	else
	{
		result = parse_ambient(*element, specs, len)
			|| parse_camera(*element, specs, len)
			|| parse_light(*element, specs, len)
			|| parse_sphere(*element, specs, len)
			|| parse_plane(*element, specs, len)
			|| parse_cylinder(*element, specs, len)
			|| parse_cone(*element, specs, len);
		if (result != 1)
			free(*element);
	}
	ft_free_split(specs);
	return (result == 1);
}

bool	parse_file(t_data *data, int fd)
{
	char		*line;
	t_element	*elem;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '#')
		{
			if (!parse_elem(line, &elem))
				return (false); // TODO: free gnl
			ft_lstadd_back(&data->elements, ft_lstnew(elem));
		}
		ft_free_set((void **) &line, get_next_line(fd));
	}
	return (true);
}
