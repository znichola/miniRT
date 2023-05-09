/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:45:28 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 14:24:08 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	get_cy_emmision(t_object *me, t_v3 poi)
{
	t_cylinder	cy;

	cy = me->object.cy;
	(void)poi;
	return (cy.colour);
}

t_v3	get_cy_position(t_object *me)
{
	t_cylinder	cy;

	cy = me->object.cy;
	return (cy.position);
}

float	get_cy_poi(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	t_cylinder	cy;

	cy = me->object.cy;
	return (poi_cylinder(&cy, ray, source, poi));
}

/* not implemented yet */
t_v3	get_cy_poi_norm(t_object *obj, t_v3 point)
{
	t_cylinder cy;

	cy = obj->object.cy;;
	(void)cy;
	(void)point;
	return ((t_v3){42,42,42});
}
