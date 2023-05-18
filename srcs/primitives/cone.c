/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:47:50 by znichola          #+#    #+#             */
/*   Updated: 2023/05/18 17:17:04 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_co_emmision(t_object *me, t_intersection *i)
{
	t_cone	co;

	co = me->object.co;
	if (co.checker)
	{
		if (get_pix_from_checkerboard(cone_map(&co, i)) == 0)
			return ((t_v3){1,1,1});
	}
	/*
		for some reason we enter this even though
		no texture map was added so it's been bypassed.
	*/
	if (0 && co.texture.img != NULL)
	{
		return (get_pix_from_texture(&co.texture, cone_map(&co, i)));
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

/* not implemented yet */
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
	map.x = 1 - (raw_u + 0.5);
	map.y = in->m / co->height;
	return (map);
}
