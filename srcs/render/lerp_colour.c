/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_colour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:23:06 by znichola          #+#    #+#             */
/*   Updated: 2023/03/16 12:13:58 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

/*
	Calculate the shade of grey based on the angle.
*/
int	colour_lerp(float min, float max, float point)
{
	int		str_col;
	int		end_col;
	double	prct;

	str_col = MRT_WHITE;
	end_col = MRT_BLACK;
	prct = (point - min) / (max - min);
	return (create_trgb(0,
			get_r(str_col) * (1 - prct) + get_r(end_col) * prct,
			get_g(str_col) * (1 - prct) + get_g(end_col) * prct,
			get_b(str_col) * (1 - prct) + get_b(end_col) * prct
		));
}

/*
	Calculate the blended resuly of the two colours.
*/
int	colour_pallet_lerp(float min, float max, float point, t_v2int pallet)
{
	double	prct;

	prct = (point - min) / (max - min);
	return (create_trgb(0,
			get_r(pallet.x) * (1 - prct) + get_r(pallet.y) * prct,
			get_g(pallet.x) * (1 - prct) + get_g(pallet.y) * prct,
			get_b(pallet.x) * (1 - prct) + get_b(pallet.y) * prct
		));
}

/*
	Add two colours
*/
int	colour_pallet_add(int x, int y)
{
	return (create_trgb(0,
			imin(get_r(x) + get_r(y), 255),
			imin(get_g(x) + get_g(y), 255),
			imin(get_b(x) + get_b(y), 255)
		));
}

/*
	light blending is super important!
	https://learnopengl.com/Lighting/Basic-Lighting
*/

/*
	multiply two colours
*/
int	colour_pallet_multiply(int x, int y)
{
	return (create_trgb(0,
			(get_r(x) * get_r(y) + 0xff) >> 8,
			(get_g(x) * get_g(y) + 0xff) >> 8,
			(get_b(x) * get_b(y) + 0xff) >> 8
		));
}

/*
	multiply a colour by an intensity/brightness
*/
int	colour_brightness_multi(int x, float b)
{
	return (create_trgb(0,
			get_r(x) * b,
			get_g(x) * b,
			get_b(x) * b
		));
}
