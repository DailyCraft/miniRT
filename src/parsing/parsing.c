/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:24:48 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 10:01:24 by dvan-hum         ###   ########.fr       */
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

static bool	parse_object(t_data *data, char **specs, size_t len)
{
	t_obj	*obj;
	int		i;
	bool	result;

	obj = ft_calloc(1, sizeof(t_obj));
	obj->shininess = 100;
	i = 0;
	result = parse_type(obj, specs[i++], len)
		&& (obj->type == TRIANGLE
			|| parse_vec(specs[i++], &obj->pos, DBL_MAX, false))
		&& (obj->type == SPHERE || obj->type == TRIANGLE
			|| parse_vec(specs[i++], &obj->dir, 1, true))
		&& parse_extra(obj, specs, &i)
		&& parse_texture(specs[i++], &obj->texture);
	while (specs[i])
	{
		result = result && parse_option(obj, specs[i]);
		i++;
	}
	ft_lstadd_back(&data->objects, ft_lstnew(obj));
	return (result);
}

static bool	parse_elem(t_data *data, char *line)
{
	char	**specs;
	size_t	len;
	bool	result;

	if (!get_specs(line, &specs, &len))
		return (true);
	printf("%s", line);
	if (!(parse_ambient(data, specs, len, &result)
			|| parse_camera(data, specs, len, &result)
			|| parse_light(data, specs, len, &result)))
		result = parse_object(data, specs, len);
	ft_free_split(specs);
	return (result);
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
	printf("\n");
	if (errno)
		return (true);
	if (!data->ambient)
		printf("1 ambiant light is required!\n");
	if (!data->cameras)
		printf("At least 1 camera is required!\n");
	return (data->ambient && data->cameras);
}
