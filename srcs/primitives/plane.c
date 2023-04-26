/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:47:01 by znichola          #+#    #+#             */
/*   Updated: 2023/04/26 12:26:48 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_structs.h"
#include "minirt_defines.h"
#include "minirt_maths.h"

t_v3	get_pl_emmision(t_object *me, t_v3 poi)
{
	t_plane	pl;

	pl = me->object.pl;
	(void)poi;
	return (pl.colour);
}


t_v3	get_pl_position(t_object *me)
{
	t_plane	pl;

	pl = me->object.pl;
	return (pl.position);
}

float	get_pl_poi(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	t_plane	pl;

	pl = me->object.pl;
	return (poi_plane(&pl, ray, source, poi));
}

t_v3	get_pl_poi_norm(t_object *obj, t_v3 point)
{
	t_plane pl;

	pl = obj->object.pl;
	return (v3_unitvec(pl.orientation));
}
