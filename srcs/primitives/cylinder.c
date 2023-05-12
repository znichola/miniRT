/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:45:28 by znichola          #+#    #+#             */
/*   Updated: 2023/05/12 17:36:57 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_cy_emmision(t_object *me, t_intersection *i)
{
	t_cylinder	cy;

	cy = me->object.cy;
	if (cy.texture.img != NULL)
	{
		return (get_pix_from_checkerboard(cylindrical_map(&cy, i)));
		//return (get_pix_from_texture(&cy.texture, cylindrical_map(&cy, i)));
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

	cy = me->object.cy;
	return (poi_cylinder(&cy, ray, source, i));
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
	//t_v3	vec;
	t_v2f	map;

	//vec = v3_subtract(v3_subtract(in->poi, cy->position), v3_multiply(cy->orientation, in->m));
/*
	t_v3 c = v3_cross(cy->orientation, UP);
	t_v3 new_up = v3_cross(c, cy->orientation);
	t_v3 right_o = v3_cross(new_up, cy->orientation);

	// c = v3_cross(in->poi_normal, UP);
	// new_up = v3_cross(c, in->poi_normal);
	// t_v3 right_poi = v3_cross(new_up, in->poi_normal);

	// vec = v3_cross(in->poi_normal, cy->orientation);
	vec = v3_cross(right_o, right_poi);
*/
/*
	vec = (t_v3){
		v3_dot(in->poi_normal, v3_cross(cy->orientation, RIGHT)),
		v3_dot(in->poi_normal, cy->orientation),
		v3_dot(in->poi_normal, v3_cross(cy->orientation, IN))
	};
*/
	t_v3 up = cy->orientation;
	t_v3 right = v3_cross(cy->orientation, UP);
	t_v3 into = v3_cross(right, cy->orientation);

	// t_v3 foo = v3_subtract(in->poi, cy->position);

	t_v3 new = (t_v3)
	{
		v3_dot(up, in->poi_normal),
		v3_dot(right, in->poi_normal),
		v3_dot(into, in->poi_normal),
	};

	// t_v3 right_poi = v3_cross(new_up, cy->orientation);

	// float	theta = atan2f(
	// 	v3_dot(in->poi_normal, v3_cross(cy->orientation, IN)),
	// 	v3_dot(in->poi_normal, cy->orientation)
	// );

	float	theta = v3_dot(UP, new) / (v3_mag(new));

	float	raw_u = theta / (2 * M_PI);

	map.x = 1 - (raw_u + 0.5);
	map.y = in->m / cy->height;
	return (map);
}