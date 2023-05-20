/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t4_determinant.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:03:22 by znichola          #+#    #+#             */
/*   Updated: 2023/05/20 10:25:45 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	t4_determinant(t_t4 t)
{
	return (
		t.m[0][0] * t4_cofactor(t, 0, 0) +
		t.m[0][1] * t4_cofactor(t, 0, 1) +
		t.m[0][2] * t4_cofactor(t, 0, 2) +
		t.m[0][3] * t4_cofactor(t, 0, 3));
}

float	t4_cofactor(t_t4 t, int i, int j)
{
	float	minor;

	minor = t4_minor(t, i, j);
	if ((i + j) % 2)
		return (-minor);
	return (minor);
}

float	t4_minor(t_t4 t, float i, float j)
{
	t_t3	sub;

	sub = t4_submatrix(t, i, j);
	return (t3_determinant(sub));
}

static void	s4(float *ret, float *t, int index_to_remove)
{
	int		i;
	int		shift;

	shift = 0;
	i = 0;
	while (i < 4)
	{
		if (i != index_to_remove)
		{
			ret[shift] = t[i];
			shift++;
		}
		i++;
	}
}

t_t3	t4_submatrix(t_t4 t, int remove_i, int remove_j)
{
	t_t3	r;
	int		i;
	int		shift;

	shift = 0;
	i = 0;
	while (i < 4)
	{
		if (i != remove_i)
		{
			s4(r.m[shift], t.m[i], remove_j);
			shift++;
		}
		i++;
	}
	return (r);
}
