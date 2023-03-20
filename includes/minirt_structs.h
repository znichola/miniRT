/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:21:27 by znichola          #+#    #+#             */
/*   Updated: 2023/03/20 17:05:13 by znichola         ###   ########.fr       */
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
}				t_v2int;

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
}				t_img_data;


/*
	used to pass process number to
	launch threads for rendering
*/
typedef struct	s_ptinfo
{
	int		id;
	void	*app;
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
	pthread_mutex_t	thread_lock[MRT_THREAD_COUNT];
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

	// world

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
	int		fov;
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
	float	diameter;
	t_v3	colour;
}	t_sphere;

typedef struct	s_plane
{
	t_v3	position;
	t_v3	orientation;
	t_v3	colour;
}	t_plane;

typedef struct	s_cylinder
{
	t_v3	position;
	t_v3	orientation;
	float	diameter;
	float	height;
	t_v3	colour;
}	t_cylinder;

union	u_object
{
	t_ambiant	a;
	t_camera	c;
	t_light		l;
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

typedef struct s_object
{
	int				type;
	union u_object	object;
}	t_object;

typedef struct	s_scene
{
	t_ambiant	ambiant;
	t_camera	camera;
	t_list		*lights_list;
	t_list		*objects_list;
}	t_scene;

#endif
