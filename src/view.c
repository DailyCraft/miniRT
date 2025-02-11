/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:19:25 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/11 17:02:32 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_light_color(t_data *data, t_element *elem, t_vec *intersection)
{
	(void) data;
	(void) elem;
	(void) intersection;
	return (elem->cylinder.color);
}

static int	get_object_color(t_data *data, t_vec *pos, t_vec *dir)
{
	float		min_dist;
	t_element	*nearest_elem;
	t_vec		hit;
	int			color;
	t_list		*lst;

	min_dist = FLT_MAX;
	nearest_elem = NULL;
	lst = data->elements;
	while (lst)
	{
		int temp = intersect(lst->content, pos, dir, &hit);
		if (temp != -1 && distance(pos, &hit) < min_dist)
		{
			color = temp;
			min_dist = distance(pos, &hit);
			nearest_elem = lst->content;
		}
		lst = lst->next;
	}
	if (nearest_elem == NULL)
		return (0);
	return (color);
	return (get_light_color(data, nearest_elem, &hit));
}

int	get_color(t_data *data, t_camera *camera, int x, int y)
{
	t_vec	vec;
	float	scale;

	scale = tan(camera->fov * M_PI / 180 / 2);
	vec.x = (2 * (x + 0.5) / WIDTH - 1) * scale * (WIDTH / HEIGHT);
	vec.y = (1 - 2 * (y + 0.5) / HEIGHT) * scale;
	vec.z = -1;
	// TODO: camera to world
	normalize(&vec);
	return (get_object_color(data, &camera->pos, &vec));
}
