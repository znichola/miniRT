/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:39:30 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 16:50:16 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_sp_emmision(t_object *me, t_intersection *i)
{
	t_sphere	sp;

	sp = me->object.sp;
	if (sp.checker || sp.texture.img != NULL
		|| sp.bump.img != NULL || sp.normal.img != NULL)
		i->map = spherical_map(&sp, i);
	if (sp.checker)
	{
		if (get_pix_from_checkerboard(i->map) == 0)
			return (CEHCKER_COLOR);
	}
	if (sp.texture.img != NULL)
	{
		return (get_pix_from_texture(&sp.texture, i->map));
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
t_v2f	spherical_map(t_sphere *sp, t_intersection *i)
{
	t_v2f	map;
	t_v3	vec;
	float	raw_u;

	vec = v3_subtract(i->poi, sp->position);
	raw_u = atan2(vec.x, vec.z) / (2 * M_PI);
	map.x = 1 - (raw_u + 0.5) + 0.5;
	map.y = (acos(vec.y / sp->radius) / M_PI);
	return (map);
}
