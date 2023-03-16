/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_control_enums.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:41:01 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 17:52:05 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_ENUMS_H
# define CONTROL_ENUMS_H

/* ~~ these are for mac! ~~ */

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

# define MOUSE_KEY_COUNT 6

enum e_mouse_key
{
	e_mouse_left = 1,
	e_mouse_right = 2,
	e_mouse_middle = 3,
	e_mouse_scroll_up = 4,
	e_mouse_scroll_down = 5,
};

# define KEYBOARD_KEY_COUNT 6

enum e_key {
	e_key_a = 0,
	e_key_s = 1,
	e_key_d = 2,
	e_key_f = 3,
	e_key_b = 11,
	e_key_w = 13,
	e_key_r = 15,
	e_key_p = 35,
	e_key_j = 38,
	e_key_n = 45,
	e_key_m = 46,
	e_key_space = 49,
	e_key_esc = 53,
	e_key_plus = 69,
	e_key_minus = 78,
	e_key_left = 123,
	e_key_right = 124,
	e_key_down = 125,
	e_key_up = 126,
};

#endif
