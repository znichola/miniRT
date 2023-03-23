/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_defines.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:32:21 by znichola          #+#    #+#             */
/*   Updated: 2023/03/23 01:10:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINES_H
# define MINIRT_DEFINES_H

// window settings
# define WIDTH 800
# define HEIGHT 800

# define ORIGIN (t_v3){0, 0, 0}
# define UP (t_v3){0, 1, 0}
# define RIGHT (t_v3){1, 0, 0}
# define IN (t_v3){0, 0, 1}

// rendering settings
# define MRT_THREAD_COUNT 4

// math constants // TODO: should be useing the ones form math.h
# define PI 		3.1415926
# define PI_HALF	1.5707963

// settings to configure the app
# define MRT_LOADING_PRINT 1U
# define MRT_DEBUG_PRINT 2U
# define MRT_MULTI_THRED 4U

# define MRT_NUM_OBJ_TYPES 6

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
