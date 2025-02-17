/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:57:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 08:49:26 by dvan-hum         ###   ########.fr       */
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

typedef union u_color
{
	int	color;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
	};
}	t_color;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	pos;
	t_vec	dir;
}	t_ray;

typedef struct s_hit
{
	t_vec	pos;
	t_vec	normal;
	//float	t;
	//bool	front_face;
}	t_hit;

typedef struct s_ambient
{
	float	brightness;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_vec	pos;
	float	brightness;
	t_color	color;
}	t_light;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	rot;
	float	fov;
	t_image	*image;
}	t_camera;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_type;

typedef struct s_object
{
	t_type	type;
	t_vec	pos;
	t_vec	rot;
	t_color	color;

	union
	{
		struct s_sphere
		{
			float	diameter;
		} sphere;
		struct s_cylinder
		{
			float	diameter;
			float	height;
		} cylinder;
		struct s_cone
		{
			float	base_width;
			float	height;
		} cone;
	};
}	t_object;

#endif
