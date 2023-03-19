/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:49:15 by znichola          #+#    #+#             */
/*   Updated: 2023/03/19 18:16:47 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_maths.h"
#include "minirt_structs.h"

#include <math.h>
#include <stdio.h>

// magnetude is the scalar quantity of the vector
// or it's length or |v| or norm
float	v3_mag(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

// the normalised or unit vector, i.e. scaled to be length 1
t_v3	v3_unitvec(t_v3 v)
{
	return (v3_divide(v, v3_mag(v)));
}

t_v3 v3_perp(t_v3 v)
{
	printf("perpedicular not implemented!\n");
	return (v);
}

// a scalar quantity
float v3_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// a vector quantity
/*
	this shit is hard look at this linky
	https://www.khanacademy.org/math/multivariable-calculus/thinking-about-multivariable-function/x786f2022:vectors-and-matrices/a/cross-products-mvc
*/
t_v3 v3_cross(t_v3 a, t_v3 b)
{
	return ((t_v3){a.y * b.z - a.z * b.y,
				 a.z * b.x - a.x * b.z,
				 a.x * b.y - a.y * b.x});
}

t_v3 v3_vadd(t_v3 a, t_v3 b)
{
	return ((t_v3){a.x + b.x, a.y + b.y, a.z + b.z});
}

// can be used to find the vector between two points
// p1 - p1 = v1
t_v3 v3_subtract(t_v3 a, t_v3 b)
{
	return ((t_v3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_v3 v3_multiply(t_v3 v, float s)
{
	return ((t_v3){v.x * s, v.y * s, v.z * s});
}

t_v3 v3_divide(t_v3 v, float s)
{
	if (s == 0)
		return (v);
	return ((t_v3){v.x / s, v.y / s, v.z / s});
}
