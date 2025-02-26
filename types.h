/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:57:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 10:00:32 by dvan-hum         ###   ########.fr       */
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
	int		width;
	int		height;
}	t_image;

typedef union u_color
{
	int	color;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
}	t_color;

typedef struct s_texture
{
	t_color	color;
	char	*image_path;
	t_image	*image;
}	t_texture;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	pos;
	t_vec	dir;
}	t_ray;

typedef struct s_ambient
{
	double	brightness;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_vec	pos;
	double	brightness;
	t_color	color;
}	t_light;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	dir;
	double	fov;
	t_image	*image;
}	t_camera;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	CONE
}	t_type;

typedef struct s_object
{
	t_type		type;
	t_vec		pos;
	t_vec		dir;
	t_texture	texture;
	bool		has_bump;
	t_texture	bump;
	bool		has_checkerboard;
	t_texture	checkerboard;
	double		shininess;
	union
	{
		struct s_sphere
		{
			double	diameter;
		} sphere;
		struct s_cylinder
		{
			double	diameter;
			double	height;
		} cylinder;
		struct s_triangle
		{
			t_vec	pos1;
			t_vec	pos2;
			t_vec	pos3;
		}	triangle;
		struct s_cone
		{
			double	base_width;
			double	height;
		} cone;
	};
}	t_obj;

typedef struct s_hit
{
	t_obj	*obj;
	t_vec	pos;
	t_vec	normal;
	double	u;
	double	v;
}	t_hit;

#endif
