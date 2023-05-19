/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t3_determinant.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:51:44 by znichola          #+#    #+#             */
/*   Updated: 2023/05/19 21:06:02 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	t3_determinant(t_t3 t)
{
	return (
		t.m[0][0] * t3_cofactor(t, 0, 0) +
		t.m[0][1] * t3_cofactor(t, 0, 1) +
		t.m[0][2] * t3_cofactor(t, 0, 2));
}

float	t3_cofactor(t_t3 t, int i, int j)
{
	float	minor;

	minor = t3_minor(t, i, j);
	if ((i + j) % 2 )
		return (-minor);
	return (minor);
}

float	t3_minor(t_t3 t, float i, float j)
{
	t_t2	sub;

	sub = t3_submatrix(t, i, j);
	return (t2_determinant(sub));
}


static void	s3(float *ret, float *t, int index_to_remove)
{
	int		i;
	int		shift;

	shift = 0;
	i = 0;
	while (i < 3)
	{
		if (i != index_to_remove)
		{
			ret[shift] = t[i];
			shift++;
		}
		i++;
	}
}

t_t2	t3_submatrix(t_t3 t, int remove_i, int remove_j)
{
	t_t2	r;
	int		i;
	int		shift;

	shift = 0;
	i = 0;
	while (i < 3)
	{
		if (i != remove_i)
		{
			s3(r.m[shift], t.m[i], remove_j);
			shift++;
		}
		i++;
	}
	return (r);
}
