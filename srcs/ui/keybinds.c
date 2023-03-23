/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:12:26 by znichola          #+#    #+#             */
/*   Updated: 2023/03/23 11:33:25 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	assign_keybinds(t_app *a)
{
	int	chagne;

	chagne = 1;
	if (/*scale_property(a, &a->s.camera.fov, "ky", e_key_f, 0.1)
		& scale_property(a, &a->s.camera.position.x, "kx-", e_key_c, 0.1)
		& scale_property(a, &a->s.camera.position.y, "ky-", e_key_c, 0.1)*/
		scale_property(a, &a->s.ambiant.ratio, "ky", e_key_a, 0.01))
	{
		chagne = 1;
		a->c_normal = v3_unitvec(a->c_normal);
	}
	a->mouse_pos_old = a->mouse_pos;
	return (chagne);
}
