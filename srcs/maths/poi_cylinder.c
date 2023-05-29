/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:46:07 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 16:54:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	center(t_terms *t, t_cylinder *me, t_intersection *i);
static float	calc_poi(t_terms *t, t_cylinder *me, t_intersection *i);
static void		wasteland(t_terms *t);

float	poi_cylinder(t_cylinder *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_terms	t;

	t.x = v3_subtract(source, me->position);
	t.dd = v3_dot(ray, ray);
	t.dv = v3_dot(ray, me->orientation);
	t.dx = v3_dot(ray, t.x);
	t.xv = v3_dot(t.x, me->orientation);
	t.xx = v3_dot(t.x, t.x);
	t.a = t.dd - t.dv * t.dv;
	t.b = (t.dx - t.dv * t.xv) * 2;
	t.c = t.xx - t.xv * t.xv - me->radius * me->radius;
	t.discrimant = t.b * t.b - 4 * t.a * t.c;
	t.radius = me->radius;
	t.ray = ray;
	t.source = source;
	t.height = me->height;
	i->poi_disance = calc_poi(&t, me, i);
	return (i->poi_disance);
}

static float	calc_poi(t_terms *t, t_cylinder *me, t_intersection *i)
{
	if (try_start_cap_sp(t, me, i) < FLT_MAX
		|| try_end_cap_sp(t, me, i) < FLT_MAX)
		return (i->poi_disance);
	if (t->discrimant < FLT_EPSILON)
	{
		i->poi_disance = FLT_MAX;
		return (FLT_MAX);
	}
	t->discrimant = sqrtf(t->discrimant);
	t->a = t->a * 2;
	t->d1 = (-t->b + t->discrimant) / t->a;
	t->d2 = (-t->b - t->discrimant) / t->a;
	t->m1 = t->dv * t->d1 + t->xv;
	t->m2 = t->dv * t->d2 + t->xv;
	wasteland(t);
	i->m = t->m2;
	i->is_cap = 0;
	if (t->m2 < t->height && t->m2 > FLT_EPSILON)
		return (center(t, me, i));
	return (FLT_MAX);
}

/*
	center or body option of the cylinder
*/
static float	center(t_terms *t, t_cylinder *me, t_intersection *i)
{
	if (t->d2 < FLT_EPSILON)
	{
		i->poi_disance = FLT_MAX;
		return (FLT_MAX);
	}
	i->poi = v3_add(t->source, v3_multiply(t->ray, t->d2));
	i->poi_normal = v3_subtract(v3_subtract(i->poi, me->position),
			v3_multiply(me->orientation, t->m2));
	i->poi_normal = v3_unitvec(i->poi_normal);
	i->poi_disance = t->d2;
	return (t->d2);
}

/*
	sets the terms so the closest poi is d2 and m2
*/
static void	wasteland(t_terms *t)
{
	float	tmp;

	if (t->d2 > t->d1)
	{
		tmp = t->d1;
		t->d1 = t->d2;
		t->d2 = tmp;
		tmp = t->m1;
		t->m1 = t->m2;
		t->m2 = tmp;
	}
}
