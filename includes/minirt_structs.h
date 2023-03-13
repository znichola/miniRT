/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:21:27 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 15:49:17 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H

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
	int		hight;
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

	t_v2int		circle;
}	t_app;


#endif
