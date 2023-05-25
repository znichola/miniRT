/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:44:32 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 12:04:47 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	*ref_obj_pos(t_object *o)
{
	if (o->type == e_sphere)
		return (&o->object.sp.position);
	else if (o->type == e_cylinder)
		return (&o->object.cy.position);
	else if (o->type == e_plane)
		return (&o->object.pl.position);
	else if (o->type == e_light)
		return (&o->object.l.position);
	else if (o->type == e_cone)
		return (&o->object.co.position);
	else if (o->type == e_camera)
		return (&o->object.c.position);
	return (NULL);
}

t_v3	*ref_obj_col(t_object *o)
{
	if (o->type == e_ambiant)
		return (&o->object.a.colour);
	else if (o->type == e_sphere)
		return (&o->object.sp.colour);
	else if (o->type == e_cylinder)
		return (&o->object.cy.colour);
	else if (o->type == e_plane)
		return (&o->object.pl.colour);
	else if (o->type == e_light)
		return (&o->object.l.colour);
	else if (o->type == e_cone)
		return (&o->object.co.colour);
	return (NULL);
}

t_v3	*ref_obj_dir(t_object *o)
{
	if (o->type == e_cylinder)
		return (&o->object.cy.orientation);
	else if (o->type == e_plane)
		return (&o->object.pl.orientation);
	else if (o->type == e_cone)
		return (&o->object.co.orientation);
	else if (o->type == e_camera)
		return (&o->object.c.orientation);
	return (NULL);
}

float	*ref_obj_p1(t_object *o)
{
	if (o->type == e_ambiant)
		return (&o->object.a.ratio);
	else if (o->type == e_sphere)
		return (&o->object.sp.radius);
	else if (o->type == e_cylinder)
		return (&o->object.cy.radius);
	else if (o->type == e_light)
		return (&o->object.l.ratio);
	else if (o->type == e_cone)
		return (&o->object.co.height_start);
	else if (o->type == e_camera)
		return (&o->object.c.fov);
	return (NULL);
}

float	*ref_obj_p2(t_object *o)
{
	if (o->type == e_cylinder)
		return (&o->object.cy.height);
	else if (o->type == e_cone)
		return (&o->object.co.height);
	return (NULL);
}
