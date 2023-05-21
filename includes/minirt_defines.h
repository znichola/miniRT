/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_defines.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:32:21 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 09:58:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINES_H
# define MINIRT_DEFINES_H

// window settings
# define WIDTH 1200
# define HEIGHT 900
// uncomment to go back after testing

// # define WIDTH  201
// # define HEIGHT 101
// remove after testing is finished!

# define ORIGIN (t_v3){0, 0, 0}
# define UP (t_v3){0, 1, 0}
# define RIGHT (t_v3){1, 0, 0}
# define IN (t_v3){0, 0, 1}

# define CEHCKER_COLOR (t_v3){1.0f, 1.0f, 1.0f}

// rendering settings
# define MRT_THREAD_COUNT 6
# define MRT_CHUNK_HEIGHT (HEIGHT / MRT_THREAD_COUNT)

// math constants // TODO: should be useing the ones form math.h
# define PI 		3.1415926
# define PI_HALF	1.5707963

// settings to configure the app
# define MRT_LOADING_PRINT 1U
# define MRT_DEBUG_PRINT 2U
# define MRT_MULTI_THRED 4U
# define MRT_PRT_TO_FILE 8U

# define MARKER 0x424242

enum {
	e_not_marked,
	e_green,
	e_cyan,
	e_fuschia,
	e_indigo
};

# define MRT_NUM_OBJ_TYPES 7

/*
	This order cannot be change at all!!
	only things can be added to the end of it.
*/
typedef enum e_obj_type
{
	e_ambiant,
	e_camera,
	e_light,
	e_sphere,
	e_plane,
	e_cylinder,
	e_cone
}	t_obj_type;

#endif
