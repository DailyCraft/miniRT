/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 07:58:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/11 16:16:25 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include "float.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "mlx.h"
# include "types.h"

# define WIDTH 1000
# define HEIGHT 1000

enum	e_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
};

typedef struct s_element
{
	enum e_type	type;
	union
	{
		t_ambient	ambient;
		t_camera	camera;
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	};
}	t_element;

typedef struct s_data
{
	void	*mlx;
	void	*window;
	t_list	*cameras;
	t_list	*elements;
}	t_data;

bool	parse_file(t_data *data, int fd);
int		parse_ambient(t_element *element, char **specs, size_t len);
int		parse_camera(t_element *element, char **specs, size_t len);
int		parse_light(t_element *element, char **specs, size_t len);
int		parse_sphere(t_element *element, char **specs, size_t len);
int		parse_plane(t_element *element, char **specs, size_t len);
int		parse_cylinder(t_element *element, char **specs, size_t len);
int		parse_cone(t_element *element, char **specs, size_t len);
bool	parsing_is_type(char *type, char *name, size_t len, size_t required);
bool	parse_vec(char *spec, t_vec *vec, float min, float max);
bool	parse_color(char *spec, int *color);
bool	parse_float(char *spec, float *value, float min, float max);
bool	parse_int(char *spec, int *value, int min, int max);

void	init_mlx(t_data *data);
t_image	*mlx_create_image(t_data *data);
int		expose_hook(t_data *data);
int		key_hook(int key, t_data *data);

int		get_color(t_data *data, t_camera *camera, int x, int y);
int		intersect(t_element *element, t_vec *pos, t_vec *dir, t_vec *hit);

void	normalize(t_vec *vec);
void	rotate_axis(float *vec1, float *vec2, float axis);
float 	distance(t_vec *pos1, t_vec *pos2);

#endif
