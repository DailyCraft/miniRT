/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:57:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/11 15:51:39 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_image
{
	void	*ptr;
	int		*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

// --- TYPES --- //

typedef struct s_ambient
{
	float	ratio;
	int		color;
}	t_ambient;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	rot;
	float	fov;
	t_image	*image;
}	t_camera;

typedef struct s_light
{
	t_vec	pos;
	float	brightness;
	int		color;
}	t_light;

typedef struct s_sphere
{
	t_vec	pos;
	float	diameter;
	int		color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	pos;
	t_vec	rot;
	int		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	pos;
	t_vec	rot;
	float	diameter;
	float	height;
	int		color;
}	t_cylinder;

typedef struct s_cone
{
	t_vec	pos;
	t_vec	rot;
	float	base_width;
	float	height;
	int		color;
}	t_cone;

#endif
