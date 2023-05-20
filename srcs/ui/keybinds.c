/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:12:26 by znichola          #+#    #+#             */
/*   Updated: 2023/05/20 12:47:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	camera_re_calc(t_app *a);
static void	obj_selection(t_app *a);

int	assign_keybinds(t_app *a)
{
	obj_selection(a);

	modify_v3(a, ref_obj_pos(a->selected), e_key_g);
	modify_v3_unitvec(a, ref_obj_dir(a->selected), e_key_t);
	modify_v3_colour(a, ref_obj_col(a->selected), e_key_y);
	mofify_float(a, ref_obj_p1(a->selected), e_key_b);
	mofify_float(a, ref_obj_p2(a->selected), e_key_h);
	mofify_float(a, ref_obj_p3(a->selected), e_key_n);

	if (a->selected->type == e_camera)
		camera_re_calc(a);

	a->mouse_pos_old = a->mouse_pos;
	return (1);
}

static void	obj_selection(t_app *a)
{
	if (a->mouse_key_click[e_mouse_left] && screen_select(a))
		printf("selecting new shape!\n");
	else if (a->keyboard_press[e_key_c])
		a->selected = &a->cam_passthrough;
	else if (a->keyboard_press[e_key_tab])
	{
		static t_list	*last_light;

		if (a->s.lights_list)
		{
			if (!last_light || !last_light->next)
				last_light = a->s.lights_list;
			else
				last_light = last_light->next;
			a->selected = last_light->content;
		}
	}
}

static void	camera_re_calc(t_app *a)
{
	if (a->s.camera.fov < 0.1f)
		a->s.camera.fov = 0.1f;
	else if (a->s.camera.fov > M_PI_2)
		a->s.camera.fov = M_PI_2;
	a->s.camera.orientation = v3_unitvec(a->s.camera.orientation);
	a->s.camera.transform = view_transform(a->s.camera.position,
		ORIGIN, a->s.camera.orientation);
	a->s.camera.inverse_transform = m4_inverse(a->s.camera.transform);
}
