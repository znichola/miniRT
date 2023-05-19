/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:43:47 by znichola          #+#    #+#             */
/*   Updated: 2023/05/19 22:24:47 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	creat the transformation matrix to move to the spesified point
*/
t_m4	translation(float x, float y, float z)
{
	return ((t_m4){
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1});
}

/*
	a.ti0 * b.t0j + a.ti1 * b.t1j + a.ti2 * b.tj2 + a.ti3 * b.tj3, //cij
*/

t_m4	m4_x_m4(t_m4 a, t_m4 b)
{
	return((t_m4){
		a.t00 * b.t00 + a.t01 * b.t10 + a.t02 * b.t02 + a.t03 * b.t03, // c00
		a.t00 * b.t01 + a.t01 * b.t11 + a.t02 * b.t12 + a.t03 * b.t13, // c01
		a.t00 * b.t02 + a.t01 * b.t12 + a.t02 * b.t22 + a.t03 * b.t23, // c02
		a.t00 * b.t03 + a.t01 * b.t13 + a.t02 * b.t32 + a.t03 * b.t33, // c03
		a.t10 * b.t00 + a.t11 * b.t10 + a.t12 * b.t02 + a.t13 * b.t03, // c10
		a.t10 * b.t01 + a.t11 * b.t11 + a.t12 * b.t12 + a.t13 * b.t13, // c11
		a.t10 * b.t02 + a.t11 * b.t12 + a.t12 * b.t22 + a.t13 * b.t23, // c12
		a.t10 * b.t03 + a.t11 * b.t13 + a.t12 * b.t32 + a.t13 * b.t33, // c13
		a.t20 * b.t00 + a.t21 * b.t10 + a.t22 * b.t02 + a.t23 * b.t03, // c20
		a.t20 * b.t01 + a.t21 * b.t11 + a.t22 * b.t12 + a.t23 * b.t13, // c21
		a.t20 * b.t02 + a.t21 * b.t12 + a.t22 * b.t22 + a.t23 * b.t23, // c22
		a.t20 * b.t03 + a.t21 * b.t13 + a.t22 * b.t32 + a.t23 * b.t33, // c23
		a.t30 * b.t00 + a.t31 * b.t10 + a.t32 * b.t02 + a.t33 * b.t03, // c30
		a.t30 * b.t01 + a.t31 * b.t11 + a.t32 * b.t12 + a.t33 * b.t13, // c31
		a.t30 * b.t02 + a.t31 * b.t12 + a.t32 * b.t22 + a.t33 * b.t23, // c32
		a.t30 * b.t03 + a.t31 * b.t13 + a.t32 * b.t32 + a.t33 * b.t33  // c33
		});
}

// t_m4	m4_inverse(t_m4 m)
// {
// 	return ((t_m4){});
// }

int	m4_is_invertable(t_t4 m)
{
	return (!!t4_determinant(m));
}
