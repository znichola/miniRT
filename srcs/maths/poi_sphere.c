/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:16:26 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/27 16:29:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Point Of Intersection with SPHERE:
	Compute the closest point of intersection between a ray and a sphere.
	The ray is defined by a source point and a ray vector.

	Returns the distace from the intersection or FLT_MAX if there is non.
*/
float	poi_sphere(t_sphere *me, t_v3 ray, t_v3 source, t_v3 *poi)
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
		if (dist1 < dist2 && dist1 > FLT_EPSILON)
		{
			*poi = v3_add(source, v3_multiply(ray, dist1));
			return (dist1);
		}
		else if (dist2 > FLT_EPSILON)
		{
			*poi = v3_add(source, v3_multiply(ray, dist2));
			return (dist2);
		}
		else
			return (FLT_MAX);
	}
	else
		return (FLT_MAX);
}
