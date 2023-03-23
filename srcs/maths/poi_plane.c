/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:26:44 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/23 11:37:17 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Point Of Intersection with plane

	Equation taken from: https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
*/
float	poi_plane(t_plane *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	float	dist;

	if (v3_dot(ray, me->orientation) == 0)
		return (FLT_MAX);
	dist = v3_dot(v3_subtract(me->position, source), me->orientation) /
		v3_dot(ray, me->orientation);
	*poi = v3_add(source, v3_multiply(ray, dist));
	return (dist);
}
