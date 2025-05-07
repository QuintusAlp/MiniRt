/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:05:05 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/28 12:59:19 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

// ************** BUILDING BLOCKS **************
typedef struct s_tuple
{
	double				x;
	double				y;
	double				z;
	int					w;
}						t_tuple;

typedef struct s_rgb
{
	double				r;
	double				g;
	double				b;
}						t_rgb;

typedef struct s_ray
{
	t_tuple				origin;
	t_tuple				direction;
}						t_ray;

// ************** MATRIX STUFF **************
typedef struct s_matrix
{
	float				**m;
	int					nbr_col;
	int					nbr_row;
	bool				square;
}						t_matrix;

typedef struct s_shearing_factors
{
	float				x_to_y;
	float				x_to_z;
	float				y_to_x;
	float				y_to_z;
	float				z_to_x;
	float				z_to_y;
}						t_shearing_factors;

// ************** LIGHT STUFF **************
typedef struct t_lighting_types
{
	t_rgb				ambient;
	t_rgb				diffuse;
	t_rgb				specular;
	t_rgb				color;
}						t_lighting_types;

typedef struct s_material
{
	t_rgb				color;
	t_lighting_types	lighting;
	double				shininess;
	t_tuple				normal;
	t_tuple				light_v;
}						t_material;

// ************** COMPUTATIONS STUFF **************
typedef struct s_delta
{
	double				a;
	double				b;
	double				c;
	double				delta;
}						t_delta;

typedef struct s_solutions
{
	double				s1;
	double				s2;
	int					s_count;
}						t_solutions;

typedef struct s_intersection
{
	char				object;
	double				t;
}						t_intersection;

// ************** FILE PARAMS **************
typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	PYRAMID,
	NONE
}						t_object_type;

typedef struct s_object
{
	t_object_type		type;
	void				*shape;
	t_material			material;
	t_tuple				(*get_normal)(struct s_object *, t_tuple);
	t_solutions			(*get_intersections)(t_ray, struct s_object *);
	struct s_object		*next;
}						t_object;

typedef struct s_ambient_light
{
	float				intensity;
	t_rgb				color;
}						t_ambient_light;

typedef struct s_camera
{
	t_ray				ray;
	float				fov;
}						t_camera;

typedef struct s_light
{
	t_tuple				origin;
	double				brightness;
	t_rgb				color;
}						t_light;

// ************** SHAPES **************

typedef struct s_plane
{
	t_tuple				origin;
	t_tuple				normal;
	t_rgb				color;
}						t_plane;

typedef struct s_sphere
{
	t_tuple				origin;
	double				radius;
	t_rgb				color;
}						t_sphere;

typedef struct s_cylinder
{
	t_tuple				center;
	t_tuple				axis;
	float				diameter;
	float				height;
	t_rgb				color;
}						t_cylinder;

typedef struct s_pyramid
{
	t_tuple				base_center;
	double				base_size;
	double				height;
	t_rgb				color;
}						t_pyramid;

// ************** MLX STUFF **************
typedef struct s_viewport
{
	t_tuple				right;
	t_tuple				up;
	float				plane_width;
	float				plane_height;
	t_tuple				top_left;
	double				step_size;
	double				rotation_angle;
}						t_viewport;

typedef struct s_scene
{
	t_ambient_light		*ambient_light;
	t_light				*light;
	t_camera			*camera;
	t_object			*objects;
	t_ray				primary;
	t_tuple				right;
	t_tuple				up;
	char				*b;
	t_object			*obj;
}						t_scene;

typedef struct s_image
{
	void				*image_ptr;
	char				*pixels_ptr;
	int					bpp;
	int					line_length;
	int					endian;
}						t_image;

typedef struct s_window
{
	void				*mlx_connection;
	void				*mlx_window;
	t_image				image;
	char				*name;
	t_viewport			viewport;
	struct s_scene		*scene;
}						t_window;

#endif
