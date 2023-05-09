/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poi_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:55:51 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 17:00:40 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*

*/
float	calculate_poi_normal(float d, t_v3 source, t_v3 ray, t_intersection i)
{
	d = sqrt(d);
	dist1 = - v3_dot(ray, w) + discrimant;
	dist2 = - v3_dot(ray, w) - discrimant;
}
