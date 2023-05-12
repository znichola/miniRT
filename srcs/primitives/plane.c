/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:47:01 by znichola          #+#    #+#             */
/*   Updated: 2023/05/12 13:12:48 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_pl_emmision(t_object *me, t_intersection *i)
{
	t_plane	pl;

	pl = me->object.pl;
	if (pl.texture.img != NULL)
	{
		return (get_pix_from_checkerboard(planar_map(&pl, i->poi)));
		//return (get_pix_from_texture(&pl.texture, planar_map(&pl, i->poi)));
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
t_v2f	planar_map(t_plane *pl, t_v3 p)
{
	(void)pl;
	float	v = ((p.x / 100) - roundf(p.x / 100));
	float	u = ((p.z / 100) - roundf(p.z / 100));
	return ((t_v2f){u, v});
}