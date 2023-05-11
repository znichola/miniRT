/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:12:26 by znichola          #+#    #+#             */
/*   Updated: 2023/05/11 22:56:02 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	assign_keybinds(t_app *a)
{
	int	chagne;

	modify_v3(a, ref_obj_pos(a->selected), e_key_g);
	// modify_v3(a, ref_obj_dir(a->selected), e_key_y);
	modify_v3_unitvec(a, ref_obj_dir(a->selected), e_key_y);
	modify_v3_colour(a, ref_obj_col(a->selected), e_key_t);
	mofify_float(a, ref_obj_p1(a->selected), e_key_r);
	mofify_float(a, ref_obj_p2(a->selected), e_key_h);

	chagne = 0;
	if (/*scale_property(a, &a->s.camera.fov, "ky", e_key_f, 0.1)
		& scale_property(a, &a->s.camera.position.x, "kx-", e_key_c, 0.1)
		& scale_property(a, &a->s.camera.position.y, "ky-", e_key_c, 0.1)*/
		scale_property(a, &get_light(&a->s, 0)->position.z, "ky", e_key_k, 0.1)
		& scale_property(a, &get_light(&a->s, 0)->position.x, "kx", e_key_l, 0.1)
		& scale_property(a, &get_light(&a->s, 0)->position.y, "ky", e_key_l, 0.1)
		& scale_property(a, &a->s.camera.fov, "kx", e_key_f, 0.001)
		& scale_property(a, &a->s.camera.position.z, "ky-", e_key_x, 0.001)
		& scale_property(a, &a->s.camera.position.x, "kx-", e_key_c, 0.001)
		& scale_property(a, &a->s.camera.position.y, "ky-", e_key_c, 0.001))
		// & scale_property(a, &a->s.ambiant.ratio, "ky", e_key_a, 0.01))
	{
		// print_v3("camera", a->s.camera.position);
		chagne = 1;
		a->c_normal = v3_unitvec(a->c_normal);
	}
	if (a->mouse_key_click[e_mouse_left] && screen_select(a))
		printf("selecting new shape!\n");
	a->mouse_pos_old = a->mouse_pos;
	return (chagne);
}
