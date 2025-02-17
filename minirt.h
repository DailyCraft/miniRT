/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 07:58:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/17 10:32:52 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include <errno.h>
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
bool	parse_vec(char *spec, t_vec *vec, double limit, bool normalized);
bool	parse_color(char *spec, t_color *color);
bool	parse_double(char *spec, double *value, double min, double max);
bool	parse_int(char *spec, int *value, int min, int max);

void	init_mlx(t_data *data);
t_image	*mlx_create_image(t_data *data);
int		expose_hook(t_data *data);
int		key_hook(int key, t_data *data);

void	update_image(t_data *data, t_camera *camera);
bool	intersect(t_object *object, t_ray *ray, t_hit *hit);

t_vec	vec_sub(t_vec *a, t_vec *b);
double	vec_dot(t_vec *a, t_vec *b);
t_vec	vec_cross(t_vec *u, t_vec *v);
t_vec	vec_mul(t_vec *v, double d);
double	get_magnitude(t_vec *vec);
void	normalize(t_vec *vec);
double	distance(t_vec *pos1, t_vec *pos2);
t_vec	ray_at(t_ray *ray, double t);

#endif
