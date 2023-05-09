/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:46:07 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 20:17:48 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i);
static t_v3		calc_normal(float dv, float xv, float t);

/*
	calculate the point at which a cylinder is intersected
	https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

*/
float	poi_cylinder(t_cylinder *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	// t_v3	end_cap;

	t_v3	x;
	float	a, b, c;
	float	dd, dv, dx, xv, xx, m;
	float	discrimant;

	float	d1, d2;

	// t_intersection i;

	(void)calc_poi;
	(void)calc_normal;

	x = v3_subtract(source, me->position);

	dd = v3_dot(ray, ray);
	dv = v3_dot(ray, me->orientation);
	dx = v3_dot(ray, x);
	xv = v3_dot(x, me->orientation);
	xx = v3_dot(x, x);

	a = dd - dv * dv;
	b = (dx - dv * xv) * 2;
	c = xx - xv * xv - me->radius * me->radius;

	discrimant = b * b - 4 * a * c;

	if (discrimant > FLT_EPSILON)
	{
		discrimant = sqrtf(discrimant);
		a = a * 2;
		d1 = (-b + discrimant) / a;
		d2 = (-b - discrimant) / a;

		if (d1 < d2 && d1 > FLT_EPSILON)
		{
			m = dv * d1 + xv;
			if (!(m > FLT_EPSILON && m < me->height))
				return (FLT_MAX);
			*poi = v3_add(source, v3_multiply(ray, d1));
			return (d1);
		}
		else if (d2 > FLT_EPSILON)
		{
			m = dv * d2 + xv;
			if (!(m > FLT_EPSILON && m < me->height))
				return (FLT_MAX);
			*poi = v3_add(source, v3_multiply(ray, d2));
			return (d2);
		}
		else
			return (d2);

		// a = calc_poi((t_v3){a, b, discrimant}, source, ray, &i);
		// *poi = i.poi;
		// calc_normal(dv, xv, discrimant); /* this is clearly wrong*/
		// return (a);
	}
	return (FLT_MAX);
}

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i)
{
	float	dsqrt;
	float	m;

	dsqrt = sqrtf(t->discrimant);
	t->d1 = (-t->b + dsqrt) / t->a;
	t->d2 = (-t->b - dsqrt) / t->a;
	if (t->d1 < t->d2 && t->d1 > FLT_EPSILON)
	{
		m = t->dv * t->d1 + t->xv;
		if (!(m > FLT_EPSILON && m < t->height))
			return (FLT_MAX);
		i->poi = v3_add(source, v3_multiply(ray, t->d1));
		return (t->d1);
	}
	else
	{
		m = t->dv * t->d2 + t->xv;
		if (!(m > FLT_EPSILON && m < t->height))
			return (FLT_MAX);
		i->poi = v3_add(source, v3_multiply(ray, t->d2));
		return (t->d2);
	}
}

static t_v3	calc_normal(float dv, float xv, float t)
{
	(void)dv;
	(void)xv;
	(void)t;
	return ((t_v3){42,42,42});
}
