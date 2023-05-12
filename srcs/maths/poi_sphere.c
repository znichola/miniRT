/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:16:26 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/12 11:30:42 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i);

/*
	Point Of Intersection with SPHERE:
	Compute the closest point of intersection between a ray and a sphere.
	The ray is defined by a source point and a ray vector.

	Returns the distace from the intersection or FLT_MAX if there is non.
*/
float	poi_sphere(t_sphere *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_terms	t;

	t.x = v3_subtract(source, me->position);
	t.a = v3_dot(ray, ray);
	t.b = v3_dot(ray, t.x) * 2;
	t.c = v3_dot(t.x, t.x) - me->radius * me->radius;
	t.discrimant = t.b * t.b - 4 * t.a * t.c;

	if (t.discrimant < FLT_EPSILON)
		i->poi_disance = FLT_MAX;
	else
	{
		i->poi_disance = calc_poi(&t, source, ray, i);
		if (i->poi_disance != FLT_EPSILON)
			i->poi_normal = v3_unitvec(v3_subtract(i->poi, me->position));
	}
	return (i->poi_disance);
}

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i)
{
	t->discrimant = sqrtf(t->discrimant);
	t->a = t->a * 2;
	t->d1 = (-t->b + t->discrimant) / t->a;
	t->d2 = (-t->b - t->discrimant) / t->a;
	if (t->d1 < t->d2 && t->d1 > FLT_EPSILON)
	{
		i->poi = v3_add(source, v3_multiply(ray, t->d1));
		i->poi_disance = t->d1;
	}
	else if (t->d2 > FLT_EPSILON)
	{
		i->poi = v3_add(source, v3_multiply(ray, t->d2));
		i->poi_disance = t->d2;
	}
	else
		return (FLT_MAX);
	return (i->poi_disance);
}
