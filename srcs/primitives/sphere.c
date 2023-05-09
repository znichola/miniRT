/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:39:30 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 21:48:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_sp_emmision(t_object *me, t_intersection *i)
{
	t_sphere	sp;

	sp = me->object.sp;
	(void)i;
	return (sp.colour);
}

t_v3	get_sp_position(t_object *me)
{
	t_sphere	sp;

	sp = me->object.sp;
	return (sp.position);
}

float	get_sp_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_sphere	sp;

	sp = me->object.sp;
	return (poi_sphere(&sp, ray, source, &i->poi));
}

t_v3	get_sp_poi_norm(t_object *obj, t_intersection *i)
{
	t_sphere	sp;

	sp = obj->object.sp;
	return (v3_unitvec(v3_subtract(i->poi, sp.position)));
}
