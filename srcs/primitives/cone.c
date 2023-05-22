/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:47:50 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 11:03:29 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_co_emmision(t_object *me, t_intersection *i)
{
	t_cone	co;

	co = me->object.co;
	if (co.checker || co.texture.img != NULL
		|| co.bump.img != NULL || co.normal.img != NULL)
		i->map = cone_map(&co, i);
	if (co.checker)
	{
		if (get_pix_from_checkerboard(i->map) == 0)
			return (CEHCKER_COLOR);
	}
	/*
		for some reason we enter this even though
		no texture map was added so it's been bypassed.
	*/
	if (co.texture.img != NULL)
	{
		return (get_pix_from_texture(&co.texture, i->map));
	}
	return (co.colour);
}

t_v3	get_co_position(t_object *me)
{
	t_cone	co;

	co = me->object.co;
	return (co.position);
}

float	get_co_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_cone	co;

	co = me->object.co;
	return (poi_cone(&co, ray, source, i));
}

t_v3	get_co_poi_norm(t_object *obj, t_intersection *i)
{
	t_cone co;

	co = obj->object.co;
	return (i->poi_normal);
}

/* map a 3d point on a colinder to a 2d point on a map */
t_v2f	cone_map(t_cone *co, t_intersection *in)
{
	t_v2f	map;

	if (in->is_cap)
		return ((t_v2f){0,0});

	t_v3 new_x = v3_cross(co->orientation, UP);
	t_v3 new_z = v3_cross(new_x, co->orientation);

	t_v3 new = (t_v3)
	{
		v3_dot(new_x, in->poi_normal),
		v3_dot(co->orientation, in->poi_normal),
		v3_dot(new_z, in->poi_normal)
	};

	float	theta = atan2(new.x, new.z);
	float	raw_u = theta / (2 * M_PI);
	map.x = (raw_u + 0.5) + 0.6;
	map.y = (in->m - co->height_start) / (co->height - co->height_start);
	return (map);
}
