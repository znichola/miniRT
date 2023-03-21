/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_defines.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:32:21 by znichola          #+#    #+#             */
/*   Updated: 2023/03/21 10:50:29 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINES_H
# define MINIRT_DEFINES_H

// window settings
# define WIDTH 800
# define HEIGHT 800

// math constants
# define PI 		3.1415926
# define PI_HALF	1.5707963

typedef enum e_obj_type
{
	e_ambiant,
	e_camera,
	e_light,
	e_sphere,
	e_plane,
	e_cylinder
}	t_obj_type;

#endif
