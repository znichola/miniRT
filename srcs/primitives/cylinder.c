/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:45:28 by znichola          #+#    #+#             */
/*   Updated: 2023/03/23 00:02:48 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_structs.h"
#include "minirt_defines.h"

#include "float.h"

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

	(void)ray;
	(void)source;
	(void)poi;
	return (FLT_MAX);
}
