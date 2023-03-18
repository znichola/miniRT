/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_control_enums.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:41:01 by znichola          #+#    #+#             */
/*   Updated: 2023/03/18 08:41:31 by znichola         ###   ########.fr       */
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

# define KEYBOARD_KEY_COUNT 127

enum e_key {
	e_key_a = 0,
	e_key_s = 1,
	e_key_d = 2,
	e_key_f = 3,
	e_key_h = 4,
	e_key_g = 5,
	e_key_z = 6,
	e_key_x = 7,
	e_key_c = 8,
	e_key_v = 9,
	e_key_b = 11,
	e_key_q = 12,
	e_key_w = 13,
	e_key_e = 14,
	e_key_r = 15,
	e_key_y = 16,
	e_key_t = 17,
	e_key_one = 18,
	e_key_two = 19,
	e_key_three = 20,
	e_key_four = 21,
	e_key_six = 22,
	e_key_five = 23,
	e_key_nine = 25,
	e_key_seven = 26,
	e_key_eight = 28,
	e_key_zero = 29,
	e_key_o = 31,
	e_key_u = 32,
	e_key_i = 34,
	e_key_p = 35,
	e_key_l = 37,
	e_key_j = 38,
	e_key_k = 40,
	e_key_n = 45,
	e_key_m = 46,
	e_key_tab = 48,
	e_key_esc = 53,
	e_key_plus = 69,
	e_key_minus = 78,
	e_key_left = 123,
	e_key_right = 124,
	e_key_down = 125,
	e_key_up = 126,
};

#endif
