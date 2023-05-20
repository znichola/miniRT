/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:39:30 by znichola          #+#    #+#             */
/*   Updated: 2023/05/17 15:51:38 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_sp_emmision(t_object *me, t_intersection *i)
{
	t_sphere	sp;

	sp = me->object.sp;
	if (sp.checker)
	{
		if (get_pix_from_checkerboard(spherical_map(&sp, i->poi)) == 0)
			return ((t_v3){0,0,0});
	}
	if (sp.texture.img != NULL)
	{
		return (get_pix_from_texture(&sp.texture, spherical_map(&sp, i->poi)));
	}
	return (sp.colour);
}

t_v3	get_sp_position(t_object *me)
{
	t_sphere	sp;

	sp = me->object.sp;
	return (sp.position);
}

float	get_sp_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_sphere	sp;

	sp = me->object.sp;
	return (poi_sphere(&sp, ray, source, i));
}

t_v3	get_sp_poi_norm(t_object *obj, t_intersection *i)
{
	t_sphere	sp;

	sp = obj->object.sp;
	return (v3_unitvec(v3_subtract(i->poi, sp.position)));
}

/* map a 3d point on a sphere to a 2d point on a map */
t_v2f	spherical_map(t_sphere *sp, t_v3 p)
{
	t_v3	vec;

	vec = v3_subtract(p, sp->position);
	float	theta = atan2(vec.x, vec.z);
	float	phi = acos(vec.y / sp->radius);
	float	raw_u = theta / (2 * M_PI);
	float	u = 1 - (raw_u + 0.5);
	float	v = 1 - (phi / M_PI);
	return ((t_v2f){u, v});
}