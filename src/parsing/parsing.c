/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:24:48 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 15:44:53 by dvan-hum         ###   ########.fr       */
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
		// TODO: return value of 2 is ignored
		result = parse_ambient(*element, specs, len)
			|| parse_camera(*element, specs, len)
			|| parse_light(*element, specs, len)
			|| parse_sphere(*element, specs, len)
			|| parse_plane(*element, specs, len)
			|| parse_cylinder(*element, specs, len)
			|| parse_cone(*element, specs, len);
		if (result == 0)
			printf("Unknown element with identifier '%s'\n", specs[0]);
		if (result != 1)
			free(*element);
	}
	ft_free_split(specs);
	return (result == 1);
}

static bool	check_parsing(t_data *data)
{
	int		ambient_count;
	t_list	*lst;

	ambient_count = 0;
	lst = data->elements;
	while (lst)
	{
		if (((t_element *) lst->content)->type == AMBIENT)
			ambient_count++;
		lst = lst->next;
	}
	if (ambient_count == 0)
		printf("At least 1 ambiant light is required!\n");
	if (!data->cameras)
		printf("At least 1 camera is required!\n");
	return (ambient_count > 0 && data->cameras);
}

static void	free_gnl(int fd, char *line)
{
	ft_free_set((void **) &line, get_next_line(fd));
	while (line)
		ft_free_set((void **) &line, get_next_line(fd));
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
			{
				free_gnl(fd, line);
				return (false);
			}
			if (elem->type == CAMERA)
			{
				ft_lstadd_back(&data->cameras,
					ft_lstnew(ft_memdup(&elem->camera, sizeof(t_camera))));
				free(elem);
			}
			else
				ft_lstadd_back(&data->elements, ft_lstnew(elem));
		}
		ft_free_set((void **) &line, get_next_line(fd));
	}
	return (check_parsing(data));
}
