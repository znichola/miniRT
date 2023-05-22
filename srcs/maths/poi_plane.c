/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:26:44 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/22 16:02:09 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Point Of Intersection with plane

	Equation taken from: https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
*/
float	poi_plane(t_plane *me, t_v3 ray, t_v3 source, t_intersection *i)
{
/*
	float	dist;

	if (v3_dot(ray, me->orientation) == 0)
		return (FLT_MAX);
	dist = v3_dot(v3_subtract(me->position, source), me->orientation) /
		v3_dot(ray, me->orientation);
	*poi = v3_add(source, v3_multiply(ray, dist));
*/
	t_terms	t;

	//me->orientation = v3_unitvec(me->orientation);

	t.x = v3_subtract(source, me->position);
	// t.x = v3_multiply(t.x, -1);
	t.xv = v3_dot(t.x, me->orientation);
	t.dv = v3_dot(ray, me->orientation);

	if (t.dv == FLT_EPSILON || ((t.xv < FLT_EPSILON) == (t.dv < FLT_EPSILON)))
		return (FLT_MAX);

	// t.d1 = t.xv / t.dv;
	i->poi_disance = - t.xv / t.dv;
	i->poi = v3_add(source, v3_multiply(ray, i->poi_disance));
	//i->poi = v3_multiply(ray, i->poi_disance);
	if (t.dv <= FLT_EPSILON)
		i->poi_normal = me->orientation;
	else
		i->poi_normal = v3_multiply(me->orientation, -1);
	return (i->poi_disance);
}

// (D*t+X)|V = 0
