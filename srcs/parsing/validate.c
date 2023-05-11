/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:53:57 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/11 12:19:46 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_orientation(t_v3 *vec)
{
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		return (-1);
	*vec = v3_unitvec(*vec);
	return (0);
}

/*
	check if all three components of colour are in [0, 255]
	reformat colour to [0, 1]
*/
int	validate_colour(t_v3 *vec)
{
	if (vec->x < 0 || vec->x > 255 || vec->y < 0 || vec->y > 255
		|| vec->z < 0 || vec->z > 255)
		return (-1);
	vec->x /= 255;
	vec->y /= 255;
	vec->z /= 255;
	return (0);
}