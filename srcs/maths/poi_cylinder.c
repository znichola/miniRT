/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:46:07 by znichola          #+#    #+#             */
/*   Updated: 2023/05/17 13:00:13 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	start_cap(t_terms *t, t_cylinder *me, t_intersection *i);
static float	end_cap(t_terms *t, t_cylinder *me, t_intersection *i);
static float	center(t_terms *t, t_cylinder *me, t_intersection *i);

static float	calc_poi(t_terms *t, t_cylinder *me, t_intersection *i);
static float	calc_poi(t_terms *t, t_cylinder *me, t_intersection *i);

/*
	calculate the point at which a cylinder is intersected
	https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

*/
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

	t.ray = ray;
	t.source = source;
	if (t.discrimant < FLT_EPSILON)
	{
		i->poi_disance = FLT_MAX;
		return (FLT_MAX);
	}

	t.height = me->height;
	i->poi_disance = calc_poi(&t, me, i);
	return (i->poi_disance);
}

int	isplus(float i)
{
	return (i > FLT_EPSILON);
}

static float	calc_poi(t_terms *t, t_cylinder *me, t_intersection *i)
{
	t->discrimant = sqrtf(t->discrimant);
	t->a = t->a * 2;
	t->d1 = (-t->b + t->discrimant) / t->a;
	t->d2 = (-t->b - t->discrimant) / t->a;

	t->m1 = t->dv * t->d1 + t->xv;
	t->m2 = t->dv * t->d2 + t->xv;

	/*
		t->dv > FLT_EPSILON
		When true the ray and orientation
		are both pointing in the same direction
		If true we are in a top cap situation,
		if false it's a bottom cap!
	*/
	if (t->dv > FLT_EPSILON)
	{
		if (t->d1 > t->d2 && t->m2 < FLT_EPSILON && t->m1 > FLT_EPSILON)
		{
			//i->is_marked = e_fuschia;
			return (start_cap(t, me, i));
		}
	}
	/*
		The orientation and dir are opposed!
	*/
	else if (t->dv < FLT_EPSILON)
	{
		if (t->d1 > t->d2 && t->m2 > t->height && t->m1 < t->height)
		{
			//i->is_marked = e_indigo;
			return (end_cap(t, me, i));
		}
	}
	if (!(t->m2 > t->height || t->m2 < FLT_EPSILON)/*something */)
	{
		i->is_marked = e_green;
		return (center(t, me, i));
	}
	return (FLT_MAX);
}

/*
	return dist, set i.poi, i.pon_normal i.poi_dist
*/
static float	start_cap(t_terms *t, t_cylinder *me, t_intersection *i)
{
	/* recompute some of the terms */
	t->xv = v3_dot(t->x, v3_multiply(me->orientation, -1));
	t->dv = v3_dot(t->ray, v3_multiply(me->orientation, -1));

	/* point of intersection*/
	i->poi_disance = - t->xv / t->dv;
	i->poi = v3_multiply(t->ray, i->poi_disance);

	/* normal at intersection */
	i->poi_normal = v3_multiply(me->orientation, -1);
	return (i->poi_disance);
}

/*
	return dist, set i.poi, i.pon_normal i.poi_dist
*/
static float	end_cap(t_terms *t, t_cylinder *me, t_intersection *i)
{
	/* recompute some of the terms */
	t->x = v3_add(t->x, v3_multiply(me->orientation, me->height));
	t->xv = v3_dot(t->x, me->orientation);

	/* point of intersection*/
	i->poi_disance = - t->xv / t->dv;
	i->poi = v3_multiply(t->ray, i->poi_disance);

	/* normal at intersection */
	i->poi_normal = me->orientation;
	return (i->poi_disance);
}

static float	center(t_terms *t, t_cylinder *me, t_intersection *i)
{
	(void)me;
	(void)t;
	(void)i;
	return (MARKER);
}
