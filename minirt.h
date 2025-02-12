/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 07:58:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/12 15:55:13 by dvan-hum         ###   ########.fr       */
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

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_list		*cameras;
	t_ambient	*ambient;
	t_list		*lights;
	t_list		*objects;
}	t_data;

bool	parse_file(t_data *data, int fd);
int		parse_ambient(t_data *data, char **specs, size_t len);
int		parse_camera(t_data *data, char **specs, size_t len);
int		parse_light(t_data *data, char **specs, size_t len);
int		parse_sphere(t_object *element, char **specs, size_t len);
int		parse_plane(t_object *element, char **specs, size_t len);
int		parse_cylinder(t_object *element, char **specs, size_t len);
int		parse_cone(t_object *element, char **specs, size_t len);
bool	parsing_is_type(char *type, char *name, size_t len, size_t required);
bool	parse_vec(char *spec, t_vec *vec, float limit, bool normalized);
bool	parse_color(char *spec, t_color *color);
bool	parse_float(char *spec, float *value, float min, float max);
bool	parse_int(char *spec, int *value, int min, int max);

void	init_mlx(t_data *data);
t_image	*mlx_create_image(t_data *data);
int		expose_hook(t_data *data);
int		key_hook(int key, t_data *data);

void	update_image(t_data *data, t_camera *camera);
bool	intersect(t_object *object, t_vec *pos, t_vec *dir, t_vec *hit);

t_vec	vec_sub(t_vec *a, t_vec *b);
float	vec_dot(t_vec *a, t_vec *b);
float	get_magnitude(t_vec *vec);
void	normalize(t_vec *vec);
float	distance(t_vec *pos1, t_vec *pos2);

#endif
