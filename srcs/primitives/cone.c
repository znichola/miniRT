/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:47:50 by znichola          #+#    #+#             */
/*   Updated: 2023/05/12 13:05:25 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_co_emmision(t_object *me, t_intersection *i)
{
	t_cone	co;

	co = me->object.co;
	(void)i;
	return (co.colour);
}

t_v3	get_co_position(t_object *me)
{
	t_cone	co;

	co = me->object.co;
	return (co.position);
}

float	get_co_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	t_cone	co;

	co = me->object.co;
	return (poi_cone(&co, ray, source, i));
}

/* not implemented yet */
t_v3	get_co_poi_norm(t_object *obj, t_intersection *i)
{
	t_cone co;

	co = obj->object.co;
	return (i->poi_normal);
}
