/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:15:48 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 11:58:18 by znichola         ###   ########.fr       */
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
		-forward.x, -forward.y, -forward.z, 0,
		0, 0, 0, 1};
	return (m4_x_m4(orientation, translation(-from.x, -from.y, -from.z)));
}

/*
	sets reusable values to the camera object, called during parsing and while
	the camera is selected.
*/
void	calculate_viewport(t_camera *c)
{
	float	half_view;
	float	aspect_ratio;
	t_v3	to;
	t_v3	new_up;

	to = v3_add(c->position, c->orientation);
	half_view = tanf(c->fov / 2.0f);
	aspect_ratio = (float)HEIGHT / WIDTH;
	if (aspect_ratio >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect_ratio;
	}
	else
	{
		c->half_width = half_view * aspect_ratio;
		c->half_height = half_view;
	}
	c->pixel_size = (c->half_width * 2) / HEIGHT;
	if (fabsf(v3_dot(c->orientation, up())) > 0.99)
		new_up = right();
	else
		new_up = up();
	c->transform = view_transform(c->position, to, new_up);
	c->inverse_transform = m4_inverse(c->transform);
}

/*
	check if a matrix is invertable
*/
int	t4_is_invertable(t_t4 m)
{
	return (!!t4_determinant(m));
}
