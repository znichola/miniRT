/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:47:01 by znichola          #+#    #+#             */
/*   Updated: 2023/03/22 23:17:11 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_structs.h"
#include "minirt_defines.h"

#include "float.h"

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

	(void)ray;
	(void)source;
	(void)poi;
	return (FLT_MAX);
}
