/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_enums.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:41:01 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 14:44:27 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_ENUMS_H
# define CONTROL_ENUMS_H

// these are for mac!
enum e_events
{
	e_on_keydown = 2,
	e_on_keyup = 3,
	e_on_mousedown = 4,
	e_on_mouseup = 5,
	e_on_mousemove = 6,
	e_on_leave = 8,
	e_on_expose = 12,
	e_on_destroy = 17,
	e_on_resize = 25,
};

enum e_mouse_key
{
	e_mouse_left = 1,
	e_mouse_right = 2,
	e_mouse_middle = 3,
	e_mouse_scroll_up = 4,
	e_mouse_scroll_down = 5,
};

#endif
