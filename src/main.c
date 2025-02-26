/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:00:36 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 09:54:29 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_args(t_data *data, int argc, char **argv)
{
	int		fd;
	bool	result;

	if (argc != 2)
	{
		printf("Welcome to miniRT created by cgrasser and dvan-hum!\n");
		printf("Usage: %s <map_file>\n", argv[0]);
		return (false);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(argv[1]), false);
	printf("Parsing file...\n");
	result = parse_file(data, fd);
	close(fd);
	if (errno)
		return (perror(argv[1]), false);
	return (result);
}

static void	free_paths(t_data *data)
{
	t_list	*lst;
	t_obj	*obj;

	lst = data->objects;
	while (lst)
	{
		obj = lst->content;
		if (obj->texture.image_path)
			free(obj->texture.image_path);
		if (obj->bump.image_path)
			free(obj->bump.image_path);
		if (obj->checkerboard.image_path)
			free(obj->checkerboard.image_path);
		lst = lst->next;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		init_mlx(&data);
	if (data.ambient)
		free(data.ambient);
	free_paths(&data);
	ft_lstclear(&data.cameras, free);
	ft_lstclear(&data.lights, free);
	ft_lstclear(&data.objects, free);
}
