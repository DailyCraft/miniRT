/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:00:36 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 09:15:31 by dvan-hum         ###   ########.fr       */
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
	result = fd >= 0 && parse_file(data, fd);
	close(fd);
	return (result);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		init_mlx(&data);
}
