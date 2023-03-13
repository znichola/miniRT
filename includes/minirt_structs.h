/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:21:27 by znichola          #+#    #+#             */
/*   Updated: 2023/03/14 00:08:01 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H

# include "minirt_control_enums.h"

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
	structure to hold all application information
	all in one big ugly struct.
*/
typedef	struct s_app
{
	t_img_data	img;
	void		*mlx_instance;
	void		*window;

	t_v2int		mouse_pos;
	int			mouse_key_click[MOUSE_KEY_COUNT];
	int			mouse_key_held[MOUSE_KEY_COUNT];
	int			mouse_key_release[MOUSE_KEY_COUNT];

	int			keyboard_press[KEYBOARD_KEY_COUNT];
	int			keyboard_held[KEYBOARD_KEY_COUNT];
	int			keyboard_release[KEYBOARD_KEY_COUNT];

	// t_v2int		circle;
	t_v3		circle;
	t_v3		light;
	// int			radius;
	float		radius;

}	t_app;


#endif
