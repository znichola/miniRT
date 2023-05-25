/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:45:51 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 12:47:40 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v2f	v2add(t_v2f a, t_v2f b)
{
	return ((t_v2f){a.x + b.x, a.y + b.y});
}

float	v2mag(t_v2f v)
{
	return (hypot(v.x, v.y));
}

t_v2f	bound(t_v2f v, float min, float max)
{
	return ((t_v2f){fmaxf(fminf(v.x, max), min), fmaxf(fminf(v.y, max), min)});
}

int	left_ofline(t_v2f s1, t_v2f s2, t_v2f cur)
{
	t_v2f	tmp;

	tmp = v2sub(s2, s1);
	return ((cur.x - s1.x) * tmp.y - (cur.y - s1.y) * tmp.x < 0);
}
