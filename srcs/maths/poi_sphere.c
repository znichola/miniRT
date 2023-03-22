/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:16:26 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/22 16:50:39 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Point Of Intersection with SPHERE:
	Compute the closest point of intersection between a ray and a sphere.
	The ray is defined by a source point and a ray vector.

	Returns 1 if there is an intersection, 0 otherwise.
*/
int poi_sphere(t_sphere *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	t_v3	w;
	float	i;
	float	j;
	float	discrimant;
	float	dist1;
	float	dist2;

	ray = v3_unitvec(ray);

	w = v3_subtract(source, me->position);

	i = powf(v3_dot(ray, w), 2);
	j = powf(v3_mag(w), 2) - powf(me->radius, 2);

	discrimant = i - j;

	if (discrimant > FLT_EPSILON)
	{
		discrimant = sqrtf(discrimant);
		dist1 = - v3_dot(ray, w) + discrimant;
		dist2 = - v3_dot(ray, w) - discrimant;
		if (dist1 < dist2 || dist2 < -FLT_EPSILON)
		{
			*poi = v3_add(source, v3_multiply(ray, dist1));
		}
		else
		{
			*poi = v3_add(source, v3_multiply(ray, dist2));
		}
		return (1);
	}
	else
		return (0);
}