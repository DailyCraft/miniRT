/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:12:38 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 11:14:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef CHEAT

# include <poll.h>

int	loop_hook(t_data *data)
{
	struct pollfd	fd;
	char			*line;

	fd.fd = STDERR_FILENO;
	fd.events = POLLIN;
	if (poll(&fd, 1, 0) <= 0)
		return (0);
	line = get_next_line(0);
	if (line == NULL)
		return (0);
	if (line[0] != '#')
	{
		if (parse_elem(data, line, false))
		{
			init_textures(data, ft_lstlast(data->objects)->content);
			expose_hook(data);
		}
		else
			mlx_loop_end(data->mlx);
	}
	free(line);
	return (0);
}

#else

int	loop_hook(t_data *data)
{
	(void) data;
	return (0);
}

#endif
