/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:59:58 by znichola          #+#    #+#             */
/*   Updated: 2023/05/20 10:25:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	this while mess of a file is for calculating the inverse of a 4x4 matrix
*/

/*
	calculate the determinat of a 2x2 this formes the base
	for the rest of the calculations
*/
float	t2_determinant(t_t2 t)
{
	return (t.m[0][0] * t.m[1][1] - t.m[0][1] * t.m[1][0]);
}

/*
	mess needed to do conversions
*/

t_t4	m4_to_t(t_m4 *m)
{
	t_t4	t;

	t.m[0][0] = m->t00;
	t.m[0][1] = m->t01;
	t.m[0][2] = m->t02;
	t.m[0][3] = m->t03;
	t.m[1][0] = m->t10;
	t.m[1][1] = m->t11;
	t.m[1][2] = m->t12;
	t.m[1][3] = m->t13;
	t.m[2][0] = m->t20;
	t.m[2][1] = m->t21;
	t.m[2][2] = m->t22;
	t.m[2][3] = m->t23;
	t.m[3][0] = m->t30;
	t.m[3][1] = m->t31;
	t.m[3][2] = m->t32;
	t.m[3][3] = m->t33;
	return (t);
}

t_m4	t4_to_m(t_t4 t)
{
	t_m4	m;

	m.t00 = t.m[0][0];
	m.t01 = t.m[0][1];
	m.t02 = t.m[0][2];
	m.t03 = t.m[0][3];
	m.t10 = t.m[1][0];
	m.t11 = t.m[1][1];
	m.t12 = t.m[1][2];
	m.t13 = t.m[1][3];
	m.t20 = t.m[2][0];
	m.t21 = t.m[2][1];
	m.t22 = t.m[2][2];
	m.t23 = t.m[2][3];
	m.t30 = t.m[3][0];
	m.t31 = t.m[3][1];
	m.t32 = t.m[3][2];
	m.t33 = t.m[3][3];
	return (m);
}
