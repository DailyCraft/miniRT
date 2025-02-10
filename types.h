/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:57:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/10 09:05:47 by dvan-hum         ###   ########.fr       */
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

struct	s_ambient
{
	float	ratio;
	int		color;
};

struct s_camera
{
	t_vec	pos;
	t_vec	axis;
	int		fov;
	t_image	*image;
};

struct s_light
{
	t_vec	pos;
	float	brightness;
	int		color;
};

struct s_sphere
{
	t_vec	pos;
	float	diameter;
	int		color;
};

struct s_plane
{
	t_vec	pos;
	t_vec	axis;
	int		color;
};

struct s_cylinder
{
	t_vec	pos;
	t_vec	axis;
	float	diameter;
	float	height;
	int		color;
};

struct s_cone
{
	t_vec	pos;
	t_vec	axis;
	float	base_width;
	float	height;
	int		color;
};

#endif
