/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:43:47 by znichola          #+#    #+#             */
/*   Updated: 2023/05/20 10:27:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	find the inverse of a matrix

	i and j are swaped for the cofactor the two to get a free tranpose
*/
t_t4	t4_inverse(t_t4 t)
{
	int		i;
	int		j;
	float	c;
	float	determinant;
	t_t4	ret;

	determinant = t4_determinant(t);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			c = t4_cofactor(t, j, i);
			ret.m[i][j] = c / determinant;
			j++;
		}
		i++;
	}
	return (ret);
}

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
	return ((t_m4){
		a.t00 * b.t00 + a.t01 * b.t10 + a.t02 * b.t02 + a.t03 * b.t03,
		a.t00 * b.t01 + a.t01 * b.t11 + a.t02 * b.t12 + a.t03 * b.t13,
		a.t00 * b.t02 + a.t01 * b.t12 + a.t02 * b.t22 + a.t03 * b.t23,
		a.t00 * b.t03 + a.t01 * b.t13 + a.t02 * b.t32 + a.t03 * b.t33,
		a.t10 * b.t00 + a.t11 * b.t10 + a.t12 * b.t02 + a.t13 * b.t03,
		a.t10 * b.t01 + a.t11 * b.t11 + a.t12 * b.t12 + a.t13 * b.t13,
		a.t10 * b.t02 + a.t11 * b.t12 + a.t12 * b.t22 + a.t13 * b.t23,
		a.t10 * b.t03 + a.t11 * b.t13 + a.t12 * b.t32 + a.t13 * b.t33,
		a.t20 * b.t00 + a.t21 * b.t10 + a.t22 * b.t02 + a.t23 * b.t03,
		a.t20 * b.t01 + a.t21 * b.t11 + a.t22 * b.t12 + a.t23 * b.t13,
		a.t20 * b.t02 + a.t21 * b.t12 + a.t22 * b.t22 + a.t23 * b.t23,
		a.t20 * b.t03 + a.t21 * b.t13 + a.t22 * b.t32 + a.t23 * b.t33,
		a.t30 * b.t00 + a.t31 * b.t10 + a.t32 * b.t02 + a.t33 * b.t03,
		a.t30 * b.t01 + a.t31 * b.t11 + a.t32 * b.t12 + a.t33 * b.t13,
		a.t30 * b.t02 + a.t31 * b.t12 + a.t32 * b.t22 + a.t33 * b.t23,
		a.t30 * b.t03 + a.t31 * b.t13 + a.t32 * b.t32 + a.t33 * b.t33
	});
}

/*
	check if a matrix is invertable
*/
int	t4_is_invertable(t_t4 m)
{
	return (!!t4_determinant(m));
}
