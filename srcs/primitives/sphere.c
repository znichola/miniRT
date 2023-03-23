/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:39:30 by znichola          #+#    #+#             */
/*   Updated: 2023/03/22 23:19:54 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_structs.h"
#include "minirt_defines.h"
#include "minirt_maths.h"

t_v3	get_sp_emmision(t_object *me, t_v3 poi)
{
	t_sphere	sp;

	sp = me->object.sp;
	(void)poi;
	return (sp.colour);
}

t_v3	get_sp_position(t_object *me)
{
	t_sphere	sp;

	sp = me->object.sp;
	return (sp.position);
}

float	get_sp_poi(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	t_sphere	sp;

	sp = me->object.sp;
	return (poi_sphere(&sp, ray, source, poi));
}
