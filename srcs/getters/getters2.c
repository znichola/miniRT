/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:44:32 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 12:03:21 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_obj_col(t_object *o)
{
	if (o->type == e_ambiant)
		return (o->object.a.colour);
	else if (o->type == e_sphere)
		return (o->object.sp.colour);
	else if (o->type == e_cylinder)
		return (o->object.cy.colour);
	else if (o->type == e_plane)
		return (o->object.pl.colour);
	else if (o->type == e_light)
		return (o->object.l.colour);
	else if (o->type == e_cone)
		return (o->object.co.colour);
	return ((t_v3){0, 0, 42});
}

t_v3	get_obj_dir(t_object *o)
{
	if (o->type == e_cylinder)
		return (o->object.cy.orientation);
	else if (o->type == e_plane)
		return (o->object.pl.orientation);
	else if (o->type == e_cone)
		return (o->object.co.orientation);
	else if (o->type == e_camera)
		return (o->object.c.orientation);
	return ((t_v3){0, 0, 42});
}

float	get_obj_p1(t_object *o)
{
	if (o->type == e_ambiant)
		return (o->object.a.ratio);
	else if (o->type == e_sphere)
		return (o->object.sp.radius);
	else if (o->type == e_cylinder)
		return (o->object.cy.radius);
	else if (o->type == e_light)
		return (o->object.l.ratio);
	else if (o->type == e_cone)
		return (o->object.co.height_start);
	else if (o->type == e_camera)
		return (o->object.c.fov);
	return (NAN);
}

float	get_obj_p2(t_object *o)
{
	if (o->type == e_cylinder)
		return (o->object.cy.height);
	if (o->type == e_cone)
		return (o->object.co.height);
	return (NAN);
}

float	get_obj_p3(t_object *o)
{
	if (o->type == e_cone)
		return (o->object.co.angle);
	return (NAN);
}
