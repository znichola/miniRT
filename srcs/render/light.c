/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:52:49 by znichola          #+#    #+#             */
/*   Updated: 2023/03/14 22:55:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	https://www.paulsprojects.net/tutorials/simplebump/simplebump.html

	The red book defines the standard OpenGL lighting equation as:

	Vertex Color = emission + globalAmbient + sum(attenuation * spotlight *
[lightAmbient + (max {L.N, 0} * diffuse) + (max {H.N, 0} ^ shininess)*specular])

	Where:
	emission		is the material's emissive color
	globalAmbient	is the ambient color*global ambient brightness
	attenuation		is a term causing lights to become dimmer with distance
	spotlight		is a term causing spotlight effects
	lightAmbient	is the light's ambient color*brightness
	diffuse			is the light's diffuse color * the material's diffuse color
	shininess		is the specular exponent, tells us how shiny a surface is
	specular		is the light's specular color * the materials specular color

	L	is the normalised(unit length) vector
		from the vertex we are lighting to the light
	N	is the unit length normal to our vertex
	H	is the normalised "half angle" vector,
		which points half way between L and the viewer (V)

*/
/*
	Calculate the resulting colour from ambient and surface colour
*/
int	calculate_px_colour(t_app *a, float angle, int	l_colour, float l_brightness , int obj_colour)
{
	int	colour_in_shadow;
	int	diffuse;

	// int	ambient_blend;
	(void)l_colour;
	(void)l_brightness;

	/*
		blend ambien with object colour, then lerp with black using ambient ratio.
	*/

	// this is actually a bit wrong!
	// ambient_blend = colour_pallet_add(a->a_colour, obj_colour);
	// colour_in_shadow = colour_pallet_lerp(0, 1, a->a_ratio, (t_v2int){MRT_BLACK, ambient_blend});

	// colour_in_shadow = colour_pallet_multiply(a->global_ambient, obj_colour);

	colour_in_shadow = colour_pallet_multiply(a->global_ambient, obj_colour);

	if (angle > PI_HALF)
		return (colour_in_shadow);

	diffuse = colour_brightness_multi(l_colour, 1 - angle / PI_HALF );
	// return MRT_PINK;

	// return colour_pallet_multiply(colour_pallet_add(obj_colour, colour_in_shadow), diffuse);

	return colour_pallet_lerp(0, PI_HALF, angle, (t_v2int){obj_colour, colour_in_shadow});

}
