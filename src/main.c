/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:00:36 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/25 18:46:17 by cgrasser         ###   ########.fr       */
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

// static void free_images(t_data *data)
// {
// 	t_list	*lst;

// 	lst = data->objects;
// 	while (lst)
// 	{
// 		if (((t_obj *) lst->content)->bump_path)
// 			free(((t_obj *) lst->content)->bump_path);
// 		lst = lst->next;
// 	}
// }

//TODO Fix free images
int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		init_mlx(&data);
	if (data.ambient)
		free(data.ambient);
	//free_images(&data);
	ft_lstclear(&data.cameras, free);
	ft_lstclear(&data.lights, free);
	ft_lstclear(&data.objects, free);
}
