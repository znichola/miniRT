/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:46:07 by znichola          #+#    #+#             */
/*   Updated: 2023/05/16 16:26:19 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i);
static void		calc_normal(t_terms *t, t_cylinder *me, t_intersection *i);
static int		count_and_set_intersection(t_terms *t);

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

	if (t.discrimant < FLT_EPSILON)
	{
		i->poi_disance = FLT_MAX;
		return (FLT_MAX);
	}

	t.height = me->height;
	i->poi_disance = calc_poi(&t, source, ray, i);

	if (i->poi_disance != FLT_EPSILON)
		calc_normal(&t, me, i);

	return (i->poi_disance);
}

static int	isplus(float i)
{
	return (i > FLT_EPSILON);
}

static float	calc_poi(t_terms *t, t_v3 source, t_v3 ray, t_intersection *i)
{
	t->discrimant = sqrtf(t->discrimant);
	t->a = t->a * 2;
	t->d1 = (-t->b + t->discrimant) / t->a;
	t->d2 = (-t->b - t->discrimant) / t->a;

	t->m1 = t->dv * t->d1 + t->xv;
	t->m2 = t->dv * t->d2 + t->xv;

	if ((!isplus(t->m1) && t->m2 > t->height))
	{
		i->is_marked = 42; //green
		return (MARKER);
	}
	if (!isplus(t->m2) && t->m1 > t->height)
	{
		i->is_marked = 43; //cyan
		return (MARKER);
	}
	if ((t->m1 > t->height || !isplus(t->m1)) && (t->m2 <= t->height && isplus(t->m2)))
	{
		i->is_marked = 44; //fuschia
		return (MARKER);
	}
	if ((t->m2 > t->height || !isplus(t->m2)) && (t->m1 <= t->height && isplus(t->m1)))
	{
		i->is_marked = 45; //indigo
		return (MARKER);
	}
	if (t->d1 < t->d2 && t->d1 > FLT_EPSILON)
	{
		/* why do we never use this part of the equation !? */
		// printf("boo, we got here in the unsed wastland...\n");
		if (count_and_set_intersection(t) == 0)
			return (FLT_MAX);
		i->poi = v3_add(source, v3_multiply(ray, t->d1));
		return (t->d1);
	}
	else if (t->d2 > FLT_EPSILON)
	{
		if (count_and_set_intersection(t) == 0)
			return (FLT_MAX);
		i->poi = v3_add(source, v3_multiply(ray, t->d2));
		return (t->d2);
	}
	return (FLT_MAX);
}

static void	calc_normal(t_terms *t, t_cylinder *me, t_intersection *i)
{
	//   N = nrm( P-C-V*m )

	if (t->message == 'b')
	{
		i->poi_normal = v3_subtract(v3_subtract(i->poi, me->position),
			v3_multiply(me->orientation, t->m));
		i->poi_normal = v3_unitvec(i->poi_normal);
		return ;
	}
	else if (t->message == '1')
	{
		// i->is_marked = 42;
		i->poi_normal = v3_multiply(me->orientation, -1);
	}
	else if (t->message == '2')
	{
		i->poi_normal = me->orientation;
	}

}

// static float	dist_to_camera(t_terms *t)
// {
// 	if (t->d1 < t->d2)
// 	{
// 		t->message = '1';
// 		t->m = t->m1;
// 		return (t->d1);
// 	}
// 	else
// 	{
// 		t->message = '2';
// 		t->m = t->m2;
// 		return (t->d2);
// 	}
// }

/*
	When trying to calculate the point of intersection the cylinder extends to
	infinity, so we must use the m value and compare it against [0, height]

	If one of the two results is outside the range, we want to take the samller
	of the two to ensure it's normal will point the right way.
	This is for an uncapped cylinder.

	To cap the cylinder to need to know which of the caps it is;
	start_cap or end_cap, to know what direction the normal should be.

	We use the message variable to communicate which cap it is to calc_normal

	'1' means it's m1 that is the closer point
	'2' means it's m2 that's closer
	'b' means both were in range so m was set to the closer one


*/
// static int	count_and_set_intersection(t_terms *t)
// {
// 	dist_to_camera(t);

// 	return (ret);
// }



































static int	count_and_set_intersection(t_terms *t)
{
	int ret;

	ret = 0;
	t->message = 'n';
	if (t->m1 > FLT_EPSILON && t->m1 < t->height)
	{
		t->m = t->m1;
		t->message = '1';
		ret += 1;
	}
	if (t->m2 > FLT_EPSILON && t->m2 < t->height)
	{
		if (ret == 0)
		{
			t->m = t->m2;
			t->message = '2';
		}
		else if (t->m2 < t->m1)
		{
			t->m = t->m2;
			t->message = 'b';
		}
		ret += 1;
	}
	return (ret);
}
