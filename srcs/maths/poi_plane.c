/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:26:44 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 16:16:50 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Point Of Intersection with plane
*/
float	poi_plane(t_plane *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_terms	t;

	t.x = v3_subtract(source, me->position);
	t.xv = v3_dot(t.x, me->orientation);
	t.dv = v3_dot(ray, me->orientation);
	if (t.dv == FLT_EPSILON || ((t.xv < FLT_EPSILON) == (t.dv < FLT_EPSILON)))
		return (FLT_MAX);
	i->poi_disance = -t.xv / t.dv;
	i->poi = v3_add(source, v3_multiply(ray, i->poi_disance));
	if (t.dv <= FLT_EPSILON)
		i->poi_normal = me->orientation;
	else
		i->poi_normal = v3_multiply(me->orientation, -1);
	return (i->poi_disance);
}
