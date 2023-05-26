/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cone2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:07 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/26 10:42:46 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		wasteland(t_terms *t);
static float	center(t_terms *t, t_cone *me, t_intersection *i);

float	calc_poi_cone(t_terms *t, t_cone *me, t_intersection *i)
{
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
	if (t->m2 < t->height && t->m2 > me->height_start)
		return (center(t, me, i));
	return (FLT_MAX);
}

/*
	sets the terms so the closest poi is d2 and m2
*/
static void	wasteland(t_terms *t)
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
	}
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
	i->poi_normal = v3_subtract(v3_subtract(i->poi, me->position),
			v3_multiply(v3_multiply(me->orientation, t->m2),
				1 + (t->k * t->k)));
	i->poi_normal = v3_unitvec(i->poi_normal);
	i->poi_disance = t->d2;
	return (t->d2);
}
