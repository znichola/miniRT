/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:15:48 by znichola          #+#    #+#             */
/*   Updated: 2023/05/20 11:00:27 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	translate a vector to a new coordinate space
	produces a transformation matrix
*/
t_m4	view_transform(t_v3 from, t_v3 to, t_v3 up)
{
	t_v3	forward;
	t_v3	upn;
	t_v3	left;
	t_v3	true_up;
	t_m4	orientation;

	forward = v3_unitvec(v3_subtract(to, from));
	upn = v3_unitvec(up);
	left = v3_cross(forward, upn);
	true_up = v3_cross(left, forward);
	orientation = (t_m4){
		left.x, left.y, left.z, 0,
		true_up.x, true_up.y, true_up.z, 0,
		-forward.x, -forward.x, forward.z, 0,
		0, 0, 0, 1};
	return (m4_x_m4(orientation, translation(-from.x, -from.y, -from.z)));
}
