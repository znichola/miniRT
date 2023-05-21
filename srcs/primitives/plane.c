/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:47:01 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 02:48:52 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_pl_emmision(t_object *me, t_intersection *i)
{
	t_plane	pl;

	pl = me->object.pl;
	if (pl.checker)
	{
		if (get_pix_from_checkerboard(planar_map(&pl, i)) == 0)
			return ((t_v3){1,1,1});
	}
	if (pl.texture.img != NULL)
	{
		return (get_pix_from_texture(&pl.texture, planar_map(&pl, i)));
	}
	return (pl.colour);
}

t_v3	get_pl_position(t_object *me)
{
	t_plane	pl;

	pl = me->object.pl;
	return (pl.position);
}

float	get_pl_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_plane	pl;

	pl = me->object.pl;
	return (poi_plane(&pl, ray, source, i));
}

t_v3	get_pl_poi_norm(t_object *obj, t_intersection *i)
{
	t_plane pl;

	pl = obj->object.pl;
	return (i->poi_normal);
}

/* map a 3d point on a plane to a 2d point on a map */
t_v2f	planar_map(t_plane *pl, t_intersection *i)
{
	t_v3	vec;
	t_v3	new_z;
	t_v3	new_x;
	t_v3	local;

	vec = v3_subtract(i->poi, pl->position);
	new_z = v3_cross(pl->orientation, RIGHT);
	new_x = v3_cross(pl->orientation, new_z);
	local = (t_v3){
		v3_dot(new_x, vec),
		v3_dot(pl->orientation, vec),
		v3_dot(new_z, vec)
	};
	return ((t_v2f){fmodf(100 - (local.x / 100), 1),
		fmodf(100 - (-local.z / 100), 1)});
}
