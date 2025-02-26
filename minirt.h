/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 07:58:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/02/26 11:05:42 by dvan-hum         ###   ########.fr       */
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
bool	parse_elem(t_data *data, char *line, bool print);
bool	parse_ambient(t_data *data, char **specs, size_t len, bool *status);
bool	parse_camera(t_data *data, char **specs, size_t len, bool *status);
bool	parse_light(t_data *data, char **specs, size_t len, bool *status);
bool	parse_type(t_obj *obj, char *spec, size_t len);
bool	parse_extra(t_obj *obj, char **specs, int *i);
bool	parse_vec(char *spec, t_vec *vec, double limit, bool normalized);
bool	parse_texture(char *spec, t_texture *texture);
bool	parse_color(char *spec, t_color *color);
bool	parse_double(char *spec, double *value, double min, double max);
bool	parse_option(t_obj *obj, char *spec);

void	init_mlx(t_data *data);
t_image	*mlx_create_image(t_data *data);
int		expose_hook(t_data *data);
int		key_hook(int key, t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);
int		loop_hook(t_data *data);

t_obj	*get_object(t_data *data, t_ray *ray, t_hit *hit, double max);
t_ray	gen_ray(t_camera *camera, int x, int y);
void	get_pixel_color(t_data *data, t_obj *object, t_hit *hit,
			t_color *color);

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

void	sphere_uv(t_hit *hit);
void	cylinder_uv(t_data *data, t_obj *object, t_hit *hit);
void	plane_uv(t_hit *hit);

void	init_images(t_data *data);
void	free_images(t_data *data);
void	init_textures(t_data *data, t_obj *obj);
void	free_textures(t_data *data, t_obj *obj);

#endif
