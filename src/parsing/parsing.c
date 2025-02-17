/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:24:48 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 15:57:48 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	get_specs(char *line, char ***specs, size_t *len)
{
	*specs = ft_split(line, " \t\n\v\f\r");
	*len = 0;
	while ((*specs)[*len])
		(*len)++;
	if (*len == 0)
	{
		ft_free_split(*specs);
		return (false);
	}
	return (true);
}

static bool	parse_object(t_data *data, char **specs, size_t len, bool *status)
{
	t_object	*object;
	bool		result;

	object = malloc(sizeof(t_object));
	object->bump_path = NULL;
	object->bump = NULL;
	result = parse_sphere(object, specs, len, status)
		|| parse_plane(object, specs, len, status)
		|| parse_cylinder(object, specs, len, status)
		|| parse_triangle(object, specs, len, status)
		|| parse_cone(object, specs, len, status);
	ft_lstadd_back(&data->objects, ft_lstnew(object));
	return (result);
}

static bool	parse_elem(t_data *data, char *line)
{
	char		**specs;
	size_t		len;
	bool		result;
	bool		status;

	if (!get_specs(line, &specs, &len))
		return (true);
	result = parse_ambient(data, specs, len, &status)
		|| parse_camera(data, specs, len, &status)
		|| parse_light(data, specs, len, &status);
	if (!result)
		result = parse_object(data, specs, len, &status);
	if (!result)
		printf("Unknown element with identifier '%s'\n", specs[0]);
	ft_free_split(specs);
	return (status);
}

static void	free_gnl(int fd, char *line)
{
	ft_free_set((void **) &line, get_next_line(fd));
	while (line)
		ft_free_set((void **) &line, get_next_line(fd));
}

bool	parse_file(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '#' && !parse_elem(data, line))
		{
			free_gnl(fd, line);
			return (false);
		}
		ft_free_set((void **) &line, get_next_line(fd));
	}
	if (errno)
		return (true);
	if (!data->ambient)
		printf("1 ambiant light is required!\n");
	if (!data->cameras)
		printf("At least 1 camera is required!\n");
	return (data->ambient && data->cameras);
}
