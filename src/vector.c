/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:24:58 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 15:28:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize(t_vec *vec)
{
	float magnitude;

	magnitude = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
}
