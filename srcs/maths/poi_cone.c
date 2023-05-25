/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:06:29 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 13:31:19 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	try_start_cap(t_terms *t, t_cone *me, t_intersection *i);
static float	try_end_cap(t_terms *t, t_cone *me, t_intersection *i);

/*
	Compute intersection (and normal) of ray with cone.
*/
float	poi_cone(t_cone *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_terms	t;

	t.k = tanf(me->angle / 2);
	t.x = v3_subtract(source, me->position);
	t.dd = v3_dot(ray, ray);
	t.dv = v3_dot(ray, me->orientation);
	t.dx = v3_dot(ray, t.x);
	t.xv = v3_dot(t.x, me->orientation);
	t.xx = v3_dot(t.x, t.x);
	t.ray = ray;
	t.source = source;
	if (try_start_cap(&t, me, i) < FLT_MAX || try_end_cap(&t, me, i) < FLT_MAX)
		return (i->poi_disance);
	t.a = t.dd - (1 + t.kk) * t.dv * t.dv;
	t.b = (t.dx - (1 + t.kk) * t.dv * t.xv) * 2;
	t.c = t.xx - (1 + t.kk) * t.xv * t.xv;
	t.discrimant = t.b * t.b - 4 * t.a * t.c;
	if (t.discrimant < FLT_EPSILON)
	{
		i->poi_disance = FLT_MAX;
		return (FLT_MAX);
	}
	t.height = me->height;
	i->poi_disance = calc_poi_cone(&t, me, i);
	return (i->poi_disance);
}

static float	try_start_cap(t_terms *t, t_cone *me, t_intersection *i)
{
	t_plane	p;

	if ((v3_dot(me->orientation, t->ray)) >= FLT_EPSILON)
	{
		p.position = v3_add(me->position,
				v3_multiply(me->orientation, me->height_start));
		p.orientation = v3_multiply(me->orientation, -1);
		poi_plane(&p, t->ray, t->source, i);
		if (v3_mag(v3_subtract(i->poi, p.position)) <= t->k * me->height_start)
		{
			i->is_cap = 1;
			return (i->poi_disance);
		}
	}
	return (FLT_MAX);
}

static float	try_end_cap(t_terms *t, t_cone *me, t_intersection *i)
{
	t_plane	p;

	if ((v3_dot(me->orientation, t->ray)) <= FLT_EPSILON)
	{
		p.position = v3_add(me->position,
				v3_multiply(me->orientation, me->height));
		p.orientation = me->orientation;
		poi_plane(&p, t->ray, t->source, i);
		if (v3_mag(v3_subtract(i->poi, p.position)) <= t->k * me->height)
		{
			i->is_cap = 1;
			return (i->poi_disance);
		}
	}
	return (FLT_MAX);
}
