/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cylinder2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:48:59 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/29 13:06:53 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	return dist, set i.poi, i.pon_normal i.poi_dist
*/
float	try_start_cap_sp(t_terms *t, t_cylinder *me, t_intersection *i)
{
	t_plane	p;

	if ((v3_dot(me->orientation, t->ray)) > FLT_EPSILON)
	{
		p.position = me->position;
		p.orientation = v3_multiply(me->orientation, -1);
		if (poi_plane(&p, t->ray, t->source, i) == FLT_MAX)
			return (FLT_MAX);
		if (v3_mag(v3_subtract(i->poi, p.position)) <= t->radius)
		{
			i->is_cap = 1;
			return (i->poi_disance);
		}
	}
	return (FLT_MAX);
}

/*
	return dist, set i.poi, i.pon_normal i.poi_dist
*/
float	try_end_cap_sp(t_terms *t, t_cylinder *me, t_intersection *i)
{
	t_plane	p;

	if ((v3_dot(me->orientation, t->ray)) < -FLT_EPSILON)
	{
		p.position = v3_add(me->position,
				v3_multiply(me->orientation, me->height));
		p.orientation = me->orientation;
		if (poi_plane(&p, t->ray, t->source, i) == FLT_MAX)
			return (FLT_MAX);
		if (v3_mag(v3_subtract(i->poi, p.position)) <= t->radius)
		{
			i->is_cap = 1;
			return (i->poi_disance);
		}
	}
	return (FLT_MAX);
}
