/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_defines.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:32:21 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 14:50:14 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINES_H
# define MINIRT_DEFINES_H

// window settings
# define WIDTH 1200
# define HEIGHT 900

// replaced with very dumb functions for the norminette
// # define ORIGIN (t_v3){0, 0, 0}
// # define UP (t_v3){0, 1, 0}
// # define RIGHT (t_v3){1, 0, 0}
// # define IN (t_v3){0, 0, 1}

// rendering settings
# define MRT_THREAD_COUNT 12
// # define MRT_CHUNK_HEIGHT (HEIGHT / MRT_THREAD_COUNT)

// colour used occasionaly
# define MRT_TRANS	0xff000000
# define MRT_WHITE	0x00ffffff
# define MRT_BLACK	0x00000000
# define MRT_PINK	0x00ff00bb

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
