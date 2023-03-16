/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:43:17 by znichola          #+#    #+#             */
/*   Updated: 2023/03/16 12:12:21 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_v3(char *name, t_v3 *v)
{
	printf("%s (%f, %f, %f)\n", name, v->x, v->y, v->z);
}

int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
