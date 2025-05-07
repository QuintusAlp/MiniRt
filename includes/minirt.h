/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:52:00 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:38:19 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "keycodes.h"
# include "structs.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifdef __APPLE__
#  include "../minilibx/mlx.h"
# else
#  include "../minilibx-l/mlx.h"
#  include "../minilibx-l/mlx_int.h"
# endif

# define WIDTH 1920
# define HEIGHT 1080
# define RED "\033[1;31m"
# define RESET "\033[0m"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef FLT_EPSILON
#  define FLT_EPSILON 1.19209290e-07F
# endif

// ************** INTERSECTIONS **************
// cylinder_intersections
t_solutions		intersect_cylinder(t_ray ray, t_object *obj);
// intersections
float			closest_intersection(t_scene *scene, t_object **obj);
int				intersect_light(t_ray light_v, t_scene *scene);
// obj_intersections
void			set_sol(t_solutions *sol, int count, double s1, double s2);
t_solutions		compute_delta(t_delta delta);
t_solutions		intersect_sphere(t_ray ray, t_object *obj);
t_solutions		intersect_plane(t_ray ray, t_object *obj);
t_tuple			ray_at(t_ray ray, double t);
// pyramid_intersections
t_solutions		intersect_pyramid(t_ray ray, t_object *obj);

// ************** MLX_STUFF **************
// events
void			events_init(t_window *window);
// mlx_init
void			window_init(t_window *window, t_scene *scene);

// ************** PARSING **************
// ambient_light
void			ft_ambiant_light(char **buffer, t_scene *data, char *b);
// camera
void			ft_camera(char **buffer, t_scene *data, char *b);
// cylinder
void			ft_cylinder(char **buffer, t_scene *data, char *b);
// light
void			ft_light(char **buffer, t_scene *data, char *b);
// parse_file_utils
int				checkrange(float nbr, float min, float max);
int				checkrgb(t_rgb *color);
int				check_vector(t_tuple *vector);
void			error_parsing(char *str, t_scene *scene);
t_object_type	get_type(char *buffer);
// parsing
t_scene			*ft_parsing(char *file);
// parse_utils2
int				split_len(char **spl);
int				check_args_number(int nbr, char **buffer);
t_matrix		create_identity_matrix(int size);
void			ft_object_addback(t_object **objects, t_object *new_object);
// plane
void			ft_plane(char **buffer, t_scene *data, char *b);
// pyramid
void			ft_pyramid(char **buffer, t_scene *data, char *b);
// set_objects
void			set_object(t_object *object, void *shape, char *type_buff);
// sphere
void			ft_sphere(char **buffer, t_scene *data, char *b);

// ************** RENDERING **************
// hits
t_ray			get_transformed_ray(t_ray initial_ray,
					t_matrix transformed_matrix);
t_solutions		sphere_ray_intersections(t_ray ray, t_sphere sphere);
float			find_hit(t_solutions intersections);
// rendering utils
void			handle_pixel(int x, int y, t_window *window);
void			image_view_port(t_window *window);
void			compute_plan_vectors(t_window *window);
// rendering_utils2
void			compute_top_left_corner(t_window *window);
void			set_primary_v(int x, int y, t_window *window);
// render
void			render(t_window *window);

// ************** SHADING **************
// normal
t_tuple			sphere_get_normal(t_object *obj, t_tuple hit);
t_tuple			plane_get_normal(t_object *obj, t_tuple world_p);
t_tuple			cylinder_get_normal(t_object *obj, t_tuple world_p);
// pyramid_normal
void			set_corners(t_pyramid *pyramid, t_tuple corners[4]);
t_tuple			pyramid_get_normal(t_object *obj, t_tuple world_p);
// shading
double			lighting(t_scene *scene, t_object *object, t_tuple position);

// ************** TUPLES STUFF **************
// tuples_operations
t_tuple			tuple_addition(t_tuple t1, t_tuple t2);
t_tuple			tuple_substraction(t_tuple t1, t_tuple t2);
t_tuple			tuple_scalar_multiplication(t_tuple t, float scalar);
float			tuple_distance(t_tuple p1, t_tuple p2);
// tuples_operations2
double			get_magnitude(t_tuple t);
void			normalize_tuple(t_tuple *v);
float			dot_product(t_tuple v1, t_tuple v2);
t_tuple			compute_cross_produt(t_tuple v1, t_tuple v2);
t_tuple			set_tuple(float x, float y, float z, float w);

// ************** VARIOUS UTILS **************
// color_utils
unsigned int	rgb_to_hex(t_rgb color);
t_rgb			color_multiply(t_rgb c1, t_rgb c2);
t_rgb			color_addition(t_rgb c1, t_rgb c2);
t_rgb			color_scal_mult(t_rgb c, float scalar);
void			set_rgb(t_rgb *colour, float r, float g, float b);
// free
void			free_matrix(float **m, int nbr_row);
void			free_split(char **split);
void			free_object(t_object *object);
void			free_scene(t_scene *scene);
// matrix_operations
void			init_zero_matrix(float **m, int row, int col);
void			init_identity_matrix(float **m, int size);
float			**allocate_matrix(int cols, int rows);
t_matrix		multiply_matrixes(t_matrix m1, t_matrix m2);
void			init_matrix(t_matrix *m, int nbr_row, int nbr_col);
// safe
void			*safe_malloc(size_t bytes);
// utils_debug
void			print_matrix(t_matrix m);
void			print_tuple(t_tuple tuple);
void			print_rgb(t_rgb color);
void			print_light(t_light light);
// utils
bool			floats_equal(double a, double b);
void			error_exit(const char *error);
t_matrix		get_matrix_from_tuple(t_tuple tuple);
t_tuple			get_tuple_from_matrix(t_matrix matrix);
t_tuple			multiply_matrix_vector(float **matrix, t_tuple vector);

#endif
