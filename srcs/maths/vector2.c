/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:22:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 16:27:07 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	v3_add(t_v3 a, t_v3 b)
{
	return ((t_v3){a.x + b.x, a.y + b.y, a.z + b.z});
}

// can be used to find the vector between two points
// p1 - p1 = v1
t_v3	v3_subtract(t_v3 a, t_v3 b)
{
	return ((t_v3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_v3	v3_multiply(t_v3 v, float s)
{
	return ((t_v3){v.x * s, v.y * s, v.z * s});
}

t_v3	v3_divide(t_v3 v, float s)
{
	if (s == 0)
		return (v);
	return ((t_v3){v.x / s, v.y / s, v.z / s});
}
