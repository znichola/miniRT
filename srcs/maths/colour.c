/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:44:09 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 12:45:39 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* helper functions for doing computations with colors */

int	v3_to_col(t_v3 v)
{
	return (create_trgb(0, v.x * 255, v.y * 255, v.z * 255));
}

t_v3	col_add(t_v3 a, t_v3 b)
{
	return ((t_v3){fminf(a.x + b.x, 1.0f),
		fminf(a.y + b.y, 1.0f),
		fminf(a.z + b.z, 1.0f)});
}

t_v3	col_multi(t_v3 a, t_v3 b)
{
	return ((t_v3){fminf(a.x * b.x, 1.0f),
		fminf(a.y * b.y, 1.0f),
		fminf(a.z * b.z, 1.0f)});
}

t_v3	col_scale(t_v3 a, float s)
{
	return ((t_v3){fminf(a.x * s, 1.0f),
		fminf(a.y * s, 1.0f),
		fminf(a.z * s, 1.0f)});
}

t_v2f	v2sub(t_v2f a, t_v2f b)
{
	return ((t_v2f){a.x - b.x, a.y - b.y});
}
