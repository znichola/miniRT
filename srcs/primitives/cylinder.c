/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:45:28 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 09:58:47 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_cy_emmision(t_object *me, t_intersection *i)
{
	t_cylinder	cy;

	cy = me->object.cy;
	if (cy.checker)
	{
		if (get_pix_from_checkerboard(i->map) == 0)
			return (CEHCKER_COLOR);
	}
	if (cy.texture.img != NULL)
	{
		return (get_pix_from_texture(&cy.texture, i->map));
	}
	return (cy.colour);
}

t_v3	get_cy_position(t_object *me)
{
	t_cylinder	cy;

	cy = me->object.cy;
	return (cy.position);
}

float	get_cy_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_cylinder	cy;
	float		distance_to_poi;

	cy = me->object.cy;
	distance_to_poi = poi_cylinder(&cy, ray, source, i);
	if (distance_to_poi < FLT_MAX
		&& (cy.checker || cy.texture.img != NULL
		|| cy.bump.img != NULL || cy.normal.img != NULL))
		i->map = cylindrical_map(&cy, i);
	return (distance_to_poi);
}

t_v3	get_cy_poi_norm(t_object *obj, t_intersection *i)
{
	t_cylinder cy;

	cy = obj->object.cy;
	return (i->poi_normal);
}

/* map a 3d point on a cylinder to a 2d point on a map */
t_v2f	cylindrical_map(t_cylinder *cy, t_intersection *in)
{
	t_v2f	map;

	if (in->is_cap)
		return ((t_v2f){0,0});

	t_v3 new_x = v3_cross(cy->orientation, UP);
	t_v3 new_z = v3_cross(new_x, cy->orientation);

	t_v3 new = (t_v3)
	{
		v3_dot(new_x, in->poi_normal),
		v3_dot(cy->orientation, in->poi_normal),
		v3_dot(new_z, in->poi_normal)
	};

	float	theta = atan2(new.x, new.z);
	float	raw_u = theta / (2 * M_PI);
	map.x = (raw_u + 0.5) + 0.6;
	map.y = in->m / cy->height;
	return (map);
}
