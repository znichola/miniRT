/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:46:07 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 21:31:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i);
static void		calc_normal(t_terms *t, t_cylinder *me, t_intersection *i);

/*
	calculate the point at which a cylinder is intersected
	https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

*/
float	poi_cylinder(t_cylinder *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	t_terms	t;
	t_intersection i;

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

	if (t.discrimant < FLT_EPSILON)
		return (FLT_MAX);

	t.height = me->height;
	i.poi_disance = calc_poi(&t, source, ray, &i);
	if (i.poi_disance != FLT_EPSILON)
		calc_normal(&t, me, &i);
	*poi = i.poi; /* should be removed */
	return (i.poi_disance);
}

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i)
{
	t->discrimant = sqrtf(t->discrimant);
	t->a = t->a * 2;
	t->d1 = (-t->b + t->discrimant) / t->a;
	t->d2 = (-t->b - t->discrimant) / t->a;

	if (t->d1 < t->d2 && t->d1 > FLT_EPSILON)
	{
		t->m1 = t->dv * t->d1 + t->xv;
		if (!(t->m1 > FLT_EPSILON && t->m1 < t->height))
			return (FLT_MAX);
		i->poi = v3_add(source, v3_multiply(ray, t->d1));
		return (t->d1);
	}
	else if (t->d2 > FLT_EPSILON)
	{
		t->m2 = t->dv * t->d2 + t->xv;
		if (!(t->m2 > FLT_EPSILON && t->m2 < t->height))
			return (FLT_MAX);
		i->poi = v3_add(source, v3_multiply(ray, t->d2));
		return (t->d2);
	}
	return (i->poi_disance);
}

static void	calc_normal(t_terms *t, t_cylinder *me, t_intersection *i)
{
	//   N = nrm( P-C-V*m )
	i->poi_normal = v3_subtract(v3_subtract(i->poi, me->position),
		v3_multiply(me->orientation, me->height));
}
