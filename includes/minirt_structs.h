/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:21:27 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 12:06:02 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H

# include <pthread.h>
# include "minirt_control_enums.h"
# include "minirt_defines.h"
# include "libft.h"

/*
	used to reprisent a pixel on the screen
	and any other tasks a 2 int stuct might be used for.
*/
typedef struct s_v2int
{
	int	x;
	int	y;
}	t_v2int;

typedef struct s_v2f
{
	float	x;
	float	y;
}	t_v2f;

/*
	3 point vector
*/
typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}	t_v3;

typedef struct s_ray
{
	t_v3	direction;
	t_v3	origin;
}	t_ray;

/*
	matrix used for vector transformations
*/
typedef struct s_mat4x4
{
	float	m[4][4];
}	t_mat4x4;

/*
	new, easier matrix definition

	00 01 02 03
	10 11 12 13
	20 21 22 23
	30 31 32 33

*/
typedef struct s_m4
{
	float	t00;
	float	t01;
	float	t02;
	float	t03;

	float	t10;
	float	t11;
	float	t12;
	float	t13;

	float	t20;
	float	t21;
	float	t22;
	float	t23;

	float	t30;
	float	t31;
	float	t32;
	float	t33;
}	t_m4;

/*
	this mess is needed for the inverse matrix
*/

typedef struct s_t4
{
	float	m[4][4];
}	t_t4;

typedef struct s_t3
{
	float	m[3][3];
}	t_t3;

typedef struct s_t2
{
	float	m[2][2];
}	t_t2;

/*
	data structure for holding image data
*/
typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*filepath;
}				t_img_data;

/*
	use to pass information between maths functions.
*/
typedef struct s_terms
{
	float	a;
	float	b;
	float	c;
	float	dd;
	float	dv;
	float	dx;
	float	xv;
	float	xx;
	float	discrimant;
	float	d1;
	float	d2;
	float	m1;
	float	m2;
	float	m;
	float	k;
	float	kk;
	float	height;
	int		message;
	t_v3	x;
	t_v3	source;
	t_v3	ray;
	float	radius;
}	t_terms;

/* used in the return to help transfer this data to avoid duplication*/
typedef struct s_intersection
{
	t_v3	poi;
	t_v3	poi_normal;
	float	poi_disance;
	float	m;
	int		is_cap;
	int		is_marked;
	t_v3	poi_bmp_normal;
	t_v2f	map;
}	t_intersection;

/* objects */

typedef struct s_ambiant
{
	float	ratio;
	t_v3	colour;
	t_v3	ambient;
}	t_ambiant;

typedef struct s_camera
{
	t_v3	position;
	t_v3	orientation;
	float	fov;
	float	half_width;
	float	half_height;
	float	pixel_size;
	t_m4	transform;
	t_m4	inverse_transform;
}	t_camera;

typedef struct s_light
{
	t_v3	position;
	float	ratio;
	t_v3	colour;
}	t_light;

typedef struct s_sphere
{
	t_v3		position;
	float		radius;
	t_v3		colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_sphere;

typedef struct s_plane
{
	t_v3		position;
	t_v3		orientation;
	t_v3		colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_plane;

typedef struct s_cylinder
{
	t_v3		position;
	t_v3		orientation;
	float		radius;
	float		height;
	t_v3		colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_cylinder;

typedef struct s_cone
{
	t_v3		position;
	t_v3		orientation;
	float		height_start;
	float		height;
	float		angle;
	t_v3		colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_cone;

union u_object
{
	t_ambiant	a;
	t_camera	c;
	t_light		l;
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
	t_cone		co;
};

typedef struct s_object
{
	t_obj_type		type;
	union u_object	object;
}	t_object;

typedef struct s_scene
{
	t_ambiant	ambiant;
	t_camera	camera;
	t_list		*lights_list;
	t_list		*objects_list;
}	t_scene;

/*
	used to pass process number to
	launch threads for rendering
*/
typedef struct s_ptinfo
{
	int		id;
	void	*app;
	int		lock;
	int		status;
}	t_ptinfo;

/*
	structure to hold all application information
	all in one big ugly struct.
*/
typedef struct s_app
{
	t_img_data		img;
	void			*mlx_instance;
	void			*window;

	t_img_data		thread_img[MRT_THREAD_COUNT];
	pthread_mutex_t	render_lock[MRT_THREAD_COUNT];
	pthread_mutex_t	start_lock[MRT_THREAD_COUNT];
	pthread_t		thread_instance[MRT_THREAD_COUNT];
	t_ptinfo		thread_info[MRT_THREAD_COUNT];

	t_v2int			mouse_pos;
	t_v2int			mouse_pos_old;
	int				mouse_key_click[MOUSE_KEY_COUNT];
	int				mouse_key_held[MOUSE_KEY_COUNT];
	int				mouse_key_release[MOUSE_KEY_COUNT];

	int				keyboard_press[KEYBOARD_KEY_COUNT];
	int				keyboard_held[KEYBOARD_KEY_COUNT];
	int				keyboard_release[KEYBOARD_KEY_COUNT];

	t_object		cam_passthrough;
	t_object		*selected;

	t_scene			s;
}	t_app;

#endif
