/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:43:47 by znichola          #+#    #+#             */
/*   Updated: 2023/03/23 10:53:57 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

t_v3 v3_multiply_matrix(t_v3 i, t_mat4x4 t)
{
	t_v3	out;
	float	w;

	out.x = (i.x * t.m[0][0] + i.y * t.m[1][0] + i.z * t.m[2][0] + t.m[3][0]);
	out.y = (i.x * t.m[0][1] + i.y * t.m[1][1] + i.z * t.m[2][1] + t.m[3][1]);
	out.z = (i.x * t.m[0][2] + i.y * t.m[1][2] + i.z * t.m[2][2] + t.m[3][2]);
	w = i.x * t.m[0][3] + i.y * t.m[1][3] + i.z * t.m[2][3] + t.m[3][3];

	if (w != 0)
	{
		out.x /= w;
		out.y /= w;
		out.z /= w;
	}
	return (out);
}

t_v3 v3_add_matrix(t_v3 i, t_mat4x4 t)
{
	t_v3	out;
	float	w;

	out.x = (i.x * t.m[0][0] + i.y * t.m[1][0] + i.z * t.m[2][0] + t.m[3][0]);
	out.y = (i.x * t.m[0][1] + i.y * t.m[1][1] + i.z * t.m[2][1] + t.m[3][1]);
	out.z = (i.x * t.m[0][2] + i.y * t.m[1][2] + i.z * t.m[2][2] + t.m[3][2]);
	w = i.x * t.m[0][3] + i.y * t.m[1][3] + i.z * t.m[2][3] + t.m[3][3];

	if (w != 0)
	{
		out.x /= w;
		out.y /= w;
		out.z /= w;
	}
	return (out);
}

t_mat4x4	direction_mat(t_v3 dir)
{
	t_v3	normal = (t_v3){0.0, 0.0, 1.0};
	t_v3	v = v3_unitvec(v3_cross(normal, dir)); // normalise
	float	phi = acosf(v3_dot(normal, dir));

	float	p_cos = cosf(phi);
	float	p_sin = sinf(phi);

	t_mat4x4	t;

	t.m[0][0] = p_cos + v.x * v.x * (1.0 - p_cos);
	t.m[1][0] = v.z * p_sin + v.y * v.x * (1.0 - p_cos);
	t.m[2][0] = -v.z * p_sin + v.z * v.x * (1.0 - p_cos);
	t.m[3][0] = 0.0;

	t.m[0][1] = -v.z * p_sin + v.x * v.y * (1.0 - p_cos);
	t.m[1][1] = p_cos + v.y * v.y * (1.0 - p_cos);
	t.m[2][1] = -v.x * p_sin + v.z * v.y * (1.0 - p_cos);
	t.m[3][1] = 0.0;

	t.m[0][1] = v.y * p_sin + v.x * v.z * (1.0 - p_cos);
	t.m[1][1] = -v.x * p_sin + v.y * v.z * (1.0 - p_cos);
	t.m[2][1] = p_cos + v.z * v.z * (1.0 - p_cos);
	t.m[3][1] = 0.0;

	t.m[0][1] = 0.0;
	t.m[1][1] = 0.0;
	t.m[2][1] = 0.0;
	t.m[3][1] = 1.0;

	return (t);
}

// matrix to rotate from (0,0,1) to specified direction
// https://stackoverflow.com/questions/52189123/c alculate-rotation-matrix-to-transform-one-vector-to-another
