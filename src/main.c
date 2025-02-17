/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:00:36 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 10:16:23 by dvan-hum         ###   ########.fr       */
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
	result = parse_file(data, fd);
	close(fd);
	if (errno)
		return (perror(argv[1]), false);
	return (result);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		init_mlx(&data);
	if (data.ambient)
		free(data.ambient);
	ft_lstclear(&data.cameras, free);
	ft_lstclear(&data.lights, free);
	ft_lstclear(&data.objects, free);
}
