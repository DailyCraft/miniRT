/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:57:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/23 20:10:58 by cgrasser         ###   ########.fr       */
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
	double	x;
	double	y;
	double	z;
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
	//double	t;
	//bool	front_face;
}	t_hit;

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

typedef struct s_texture
{
    void    *img;        // L'image chargée
    int     *data;       // Les données de l'image (pixels)
    int     width;       // Largeur de l'image
    int     height;      // Hauteur de l'image
} t_texture;

typedef struct s_object
{
	t_type	type;
	t_vec	pos;
	t_vec	rot;
	t_color	color;
	char	*bump_path;	
	t_image	*bump;
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
			t_vec	x;
			t_vec	y;
			t_vec	z;
		}	triangle;
		struct s_cone
		{
			double	base_width;
			double	height;
		} cone;
	};
}	t_object;

#endif
