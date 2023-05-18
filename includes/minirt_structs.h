/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:21:27 by znichola          #+#    #+#             */
/*   Updated: 2023/05/18 11:49:38 by znichola         ###   ########.fr       */
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
typedef struct	s_v2int
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

/*
	matrix used for vector transformations
*/
typedef struct s_mat4x4
{
	float	m[4][4];
}	t_mat4x4;

/*
	data structure for holding image data
*/
typedef struct	s_img_data
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
typedef struct	s_terms
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
}	t_terms;

/* used in the return to help transfer this data to avoid duplication*/
typedef struct	s_intersection
{
	t_v3	poi;
	t_v3	poi_normal;
	float	poi_disance;
	float	m;
	int		is_cap;
	int		is_marked;
}	t_intersection;

/* objects */

typedef struct	s_ambiant
{
	float	ratio;
	t_v3	colour;
}	t_ambiant;

typedef struct	s_camera
{
	t_v3	position;
	t_v3	orientation;
	float	fov;
}	t_camera;

typedef struct	s_light
{
	t_v3	position;
	float	ratio;
	t_v3	colour;
}	t_light;

typedef struct	s_sphere
{
	t_v3	position;
	float	radius;
	t_v3	colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_sphere;

typedef struct	s_plane
{
	t_v3	position;
	t_v3	orientation;
	t_v3	colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_plane;

typedef struct	s_cylinder
{
	t_v3	position;
	t_v3	orientation;
	float	radius;
	float	height;
	t_v3	colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_cylinder;

typedef struct	s_cone
{
	t_v3	position;
	t_v3	orientation;
	float	height_start;
	float	height;
	float	angle;
	t_v3	colour;
	t_img_data	texture;
	t_img_data	bump;
	t_img_data	normal;
	int			checker;
}	t_cone;

union	u_object
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

typedef struct	s_scene
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
typedef struct	s_ptinfo
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
typedef	struct s_app
{
	t_img_data	img;
	void		*mlx_instance;
	void		*window;

	t_img_data		thread_img[MRT_THREAD_COUNT];
	pthread_mutex_t	render_lock[MRT_THREAD_COUNT];
	pthread_mutex_t	start_lock[MRT_THREAD_COUNT];
	pthread_t		thread_instance[MRT_THREAD_COUNT];
	t_ptinfo		thread_info[MRT_THREAD_COUNT];

	t_v2int		mouse_pos;
	t_v2int		mouse_pos_old;
	int			mouse_key_click[MOUSE_KEY_COUNT];
	int			mouse_key_held[MOUSE_KEY_COUNT];
	int			mouse_key_release[MOUSE_KEY_COUNT];

	int			keyboard_press[KEYBOARD_KEY_COUNT];
	int			keyboard_held[KEYBOARD_KEY_COUNT];
	int			keyboard_release[KEYBOARD_KEY_COUNT];

	t_object	*selected;

	// world
	t_scene		s;

	// ambient light
	float		a_ratio;
	int			a_colour;
		// calculated from input
	int			global_ambient;

	// camera
	t_v3		c_origin;
	t_v3		c_normal;
	float		c_viewport_offset;
	float		c_fov;
	float		c_aspect_ratio;
	t_mat4x4	c_mat;

	// objects in scene

	// light
	t_v3		l_origin;
	float		l_brightness;
	int			l_colour;

	// sphere
	t_v3		sp_origin;
	float		sp_radius;
	int			sp_colour;

	// plane
	t_v3		pl_origin;
	t_v3		pl_normal;
	int			pl_colour;

	// cylinder
	t_v3		cy_origin;
	t_v3		cy_normal;
	float		cy_diameter;
	float		cy_height;
	int			cy_colour;

}	t_app;

#endif
