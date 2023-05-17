/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:47:01 by znichola          #+#    #+#             */
/*   Updated: 2023/05/18 00:00:16 by znichola         ###   ########.fr       */
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

#define DIV 50.0f

/* map a 3d point on a plane to a 2d point on a map */
t_v2f	planar_map(t_plane *pl, t_intersection *i)
{
	t_v3 new_x = v3_cross(pl->orientation, UP);
	t_v3 new_z = v3_cross(new_x, pl->orientation);

	t_v3 pos = v3_subtract(i->poi, pl->position);
	float d = v3_mag(pos);
	pos = v3_unitvec(pos);
	t_v3 new = (t_v3)
	{
		v3_dot(new_x, pos),
		v3_dot(pl->orientation, pos),
		v3_dot(new_z, pos)
	};
	new = v3_multiply(new, d);
	// float	v = ((new.x / DIV) - roundf(new.x / DIV));
	// float	u = ((new.z / DIV) - roundf(new.z / DIV));
	// float		u = fmodf(new.x, DIV);
	// float		v = fmodf(new.z, DIV);
	// printf("u:%.1f\n", u);
	(void)pl;
	(void)new;
	float	u = ((i->poi.z / DIV) - roundf(i->poi.z / DIV));
	float	v = ((i->poi.x / DIV) - roundf(i->poi.x / DIV));
	// u = fabsf(u);
	// v = fabsf(v);
	return ((t_v2f){u, v});
}
