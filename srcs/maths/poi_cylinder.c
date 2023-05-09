/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:46:07 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 17:18:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calc_poi(t_v3 terms, t_v3 source, t_v3 ray, t_intersection *i);
static t_v3		calc_normal();

/*
	calculate the point at which a cylinder is intersected

*/
float	poi_cylinder(t_cylinder *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_v3	x;
	float	a, b, c;
	float	dd, dv, dx, xv, xx;
	float	discrimant;
	float	dist1, dist2;

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
		// printf("kajshd\n");
		discrimant = sqrtf(discrimant);
		a = a * 2;
		dist1 = (-b + discrimant) / a;
		dist2 = (-b - discrimant) / a;

		if (dist1 < dist2 && dist1 > FLT_EPSILON)
		{
			i->poi = v3_add(source, v3_multiply(ray, dist1));
			return (dist1);
		}
		else if (dist2 > FLT_EPSILON)
		{
			i->poi = v3_add(source, v3_multiply(ray, dist2));
			return (dist2);
		}
		else
			return (FLT_MAX);
	}
	return (FLT_MAX);
}

static float	calc_poi(t_v3 terms, t_v3 source, t_v3 ray, t_intersection *i)
{
	float	discrimant;
	float	d1;
	float	d2;
	float	a;
	float	b;

	a = terms.x;
	b = terms.y;
	discrimant = sqrtf(terms.z);
	d1 = (-b + discrimant) / a;
	d2 = (-b - discrimant) / a;
	if (d1 < d2 && d1 > FLT_EPSILON)
	{
		i->poi = v3_add(source, v3_multiply(ray, d1));
		return (d1);
	}
	else
	{
		i->poi = v3_add(source, v3_multiply(ray, d2));
		return (d2);
	}
}

static t_v3	calc_normal(float dv, float xv, float t)
{
	(void)dv;
	(void)xv;
	(void)t;
	return ((t_v3){42,42,42});
}
