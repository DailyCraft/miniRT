/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:19:25 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 16:15:42 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int get_light_color(t_data *data, t_element *elem, t_vec *intersection)
{
	(void) data;
	(void) elem;
	(void) intersection;
	return (elem->cylinder.color);
}

static int get_object_color(t_data *data, t_vec *pos, t_vec *vec)
{
	t_element	*nearest_elem;
	t_vec		*nearest_intersection;
	t_list		*lst;

	return ft_rgb((int) fabs(vec->x * 100), (int) fabs(vec->y * 100), (int) fabs(vec->z * 100));
	//return ft_rgb((vec->x + 1) * 0.5, (vec->y + 1) * 0.5, (vec->z + 1) * 0.5);
	nearest_elem = NULL;
	nearest_intersection = NULL;
	lst = data->elements;
	while (lst)
	{
		(void) vec;
		(void) pos;
		nearest_elem = lst->content;
		lst = lst->next;
	}
	if (nearest_elem == NULL)
		return (0);
	return (get_light_color(data, nearest_elem, nearest_intersection));
}

int	get_color(t_data *data, t_camera *camera, int x, int y)
{
	t_vec	vec;
	float	scale;

	scale = tan(camera->fov * M_PI / 180 / 2);
	vec.x = (2 * (x + 0.5) / WIDTH - 1) * scale;
	vec.y = (1 - 2 * (y + 0.5) / HEIGHT) * scale;
	vec.z = -1;
	// Rotate vector
	normalize(&vec);
	return (get_object_color(data, &camera->pos, &vec));
}