/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 07:58:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/25 18:56:11 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <errno.h>
# include "float.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
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
	t_obj		*selected;
}	t_data;

bool	parse_file(t_data *data, int fd);
bool	parse_ambient(t_data *data, char **specs, size_t len, bool *status);
bool	parse_camera(t_data *data, char **specs, size_t len, bool *status);
bool	parse_light(t_data *data, char **specs, size_t len, bool *status);
bool	parse_sphere(t_obj *object, char **specs, size_t len, bool *status);
bool	parse_plane(t_obj *object, char **specs, size_t len, bool *status);
bool	parse_cylinder(t_obj *object, char **specs, size_t len,
			bool *status);
bool	parse_triangle(t_obj *object, char **specs, size_t len,
			bool *status);
bool	parse_cone(t_obj *object, char **specs, size_t len, bool *status);
bool	parsing_is_type(char *type, char *name, size_t len, size_t required);
bool	parse_vec(char *spec, t_vec *vec, double limit, bool normalized);
bool	parse_texture(char *spec, t_obj *object);
bool	parse_color(char *spec, t_color *color);
bool	parse_double(char *spec, double *value, double min, double max);
bool	parse_bump(char *spec, char **path);

void	init_mlx(t_data *data);
t_image	*mlx_create_image(t_data *data);
int		expose_hook(t_data *data);
int		key_hook(int key, t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);

t_obj	*get_object(t_data *data, t_ray *ray, t_hit *hit, double max);
t_ray	gen_ray(t_camera *camera, int x, int y);
int		get_pixel_color(t_data *data, t_obj *object, t_hit *hit);

void	update_image(t_data *data, t_camera *camera);
bool	intersect(t_obj *object, t_ray *ray, t_hit *hit);

t_vec	vec_add(t_vec *u, t_vec *v);
t_vec	vec_sub(t_vec a, t_vec b);
double	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec *u, t_vec *v);
t_vec	vec_mul(t_vec *v, double d);
double	get_magnitude(t_vec *vec);
void	normalize(t_vec *vec);
double	distance(t_vec *pos1, t_vec *pos2);
t_vec	ray_at(t_ray *ray, double t);

#endif
