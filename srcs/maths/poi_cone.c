/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:06:29 by znichola          #+#    #+#             */
/*   Updated: 2023/05/24 17:59:23 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	center(t_terms *t, t_cone *me, t_intersection *i);

static float	calc_poi(t_terms *t, t_cone *me, t_intersection *i);
static void	wasteland(t_terms *t, t_intersection *i);
// static void		wasteland(t_terms *t);

/*
	calculate the point at which a cylinder is intersected
	https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

*/
float	poi_cone(t_cone *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_terms	t;

	t.k = tanf(me->angle/2);
	t.kk = t.k * t.k;

	t.x = v3_subtract(source, me->position);
	t.dd = v3_dot(ray, ray);
	t.dv = v3_dot(ray, me->orientation);
	t.dx = v3_dot(ray, t.x);
	t.xv = v3_dot(t.x, me->orientation);
	t.xx = v3_dot(t.x, t.x);

	/*
		WE did some cool things in identifying the weirdness with the caps
		see the cyclinder code.
	*/

	/* END CAP*/
	if ((v3_dot(me->orientation, ray)) <= FLT_EPSILON)
	{
		t_plane	p;
		p.position = v3_add(me->position, v3_multiply(me->orientation, me->height));
		p.orientation = me->orientation;
		poi_plane(&p, ray, source, i);

		if (v3_mag(v3_subtract(i->poi, p.position)) <= t.k * me->height)
		{
			i->is_cap = 1;
			return (i->poi_disance);
		}
	}

	/* START CAP */
	if ((v3_dot(me->orientation, ray)) >= FLT_EPSILON)
	{
		t_plane	p;
		p.position = v3_add(me->position, v3_multiply(me->orientation, me->height_start));
		p.orientation = v3_multiply(me->orientation, -1);
		poi_plane(&p, ray, source, i);

		if (v3_mag(v3_subtract(i->poi, p.position)) <= t.k * me->height_start)
		{
			i->is_cap = 1;
			return (i->poi_disance);
		}
	}

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
	t.ray = ray;
	t.source = source;
	i->poi_disance = calc_poi(&t, me, i);
	return (i->poi_disance);
}

#include <assert.h>

static float	calc_poi(t_terms *t, t_cone *me, t_intersection *i)
{
	t->discrimant = sqrtf(t->discrimant);
	t->a = t->a * 2;
	t->d1 = (-t->b + t->discrimant) / t->a;
	t->d2 = (-t->b - t->discrimant) / t->a;

	t->m1 = t->dv * t->d1 + t->xv;
	t->m2 = t->dv * t->d2 + t->xv;

	wasteland(t, i);
	i->m = t->m2;
	i->is_cap = 0;

	if (t->m2 < t->height && t->m2 > me->height_start)
	{
		return (center(t, me, i));
	}
	return (FLT_MAX);
}

/*
	center or body option of the cone
	N = nrm( P-C - (1+k*k)*V*m )
*/
static float	center(t_terms *t, t_cone *me, t_intersection *i)
{
	if (t->d2 < FLT_EPSILON)
	{
		i->poi_disance = FLT_MAX;
		return (FLT_MAX);
	}
	i->poi = v3_add(t->source, v3_multiply(t->ray, t->d2));

	i->poi_normal = v3_subtract(v3_subtract(i->poi, me->position), v3_multiply(v3_multiply(me->orientation, t->m2), 1 + t->kk));

	//i->poi_normal = v3_subtract(v3_subtract(i->poi, me->position), v3_multiply(me->orientation, t->m2));
	i->poi_normal = v3_unitvec(i->poi_normal);
	i->poi_disance = t->d2;
	return (t->d2);
}


/*
	sets the terms so the closest poi is d2 and m2
*/
static void	wasteland(t_terms *t, t_intersection *i)
{
	float	tmp;

	if (t->d2 > t->d1 && t->m2 < 0)
	{
		tmp = t->d1;
		t->d1 = t->d2;
		t->d2 = tmp;
		tmp = t->m1;
		t->m1 = t->m2;
		t->m2 = tmp;
		// i->is_marked = e_fuschia;
		(void)i;
	}
}
