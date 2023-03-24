/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:43:17 by znichola          #+#    #+#             */
/*   Updated: 2023/03/24 12:38:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_v3(char *name, t_v3 v)
{
	printf("%s (%f, %f, %f)\n", name, v.x, v.y, v.z);
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

void	print_image(t_app *a)
{
	for (int x = 0; x < a->img.width; x++)
		for (int y = 0; y < a->img.height; y++)
			my_mlx_pixel_put(&a->img, x, y, moon_texture(a, x, y));
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);

	usleep(100000);
}
