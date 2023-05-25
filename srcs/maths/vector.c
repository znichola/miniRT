/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:49:15 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 16:26:26 by skoulen          ###   ########.fr       */
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
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

// the normalised or unit vector, i.e. scaled to be length 1
t_v3	v3_unitvec(t_v3 v)
{
	return (v3_divide(v, v3_mag(v)));
}

float	v3_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_v3	v3_cross(t_v3 a, t_v3 b)
{
	return ((t_v3){a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}
