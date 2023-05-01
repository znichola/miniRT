/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:49:29 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/01 10:50:47 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v2int	world_to_screen(t_app *a, t_v3 world)
{
	t_v3	p0 = world;
	t_v3	p1 = v3_add(a->s.camera.position, a->s.camera.orientation);

	t_v3	pco = p1;
	t_v3	pno = a->s.camera.orientation;

	t_v3	u;
	float	dot;

	u = v3_subtract(p1, p0);
	dot = v3_dot(pno, u);

	if (fabsf(dot) > FLT_EPSILON)
	{
		t_v3	w = v3_subtract(p0, pco);
		float	fac = - v3_dot(pno, w) / dot;
		u = v3_multiply(u, fac);
		t_v3	ans = v3_add(p0, u);
		return ((t_v2int){get_world_to_pix_ratio(a, 'w', -ans.x),
						get_world_to_pix_ratio(a, 'h', -ans.y)});
	}
	return ((t_v2int){0, 0});
}

