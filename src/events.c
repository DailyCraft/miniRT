/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:17:06 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 08:32:10 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int key, t_data *data)
{
	if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	else if (key == XK_c)
	{
	}
	return (0);
}

int	expose_hook(t_data *data)
{
	(void) data;
	return (0);
}
