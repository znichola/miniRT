/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:52:49 by znichola          #+#    #+#             */
/*   Updated: 2023/03/16 13:27:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

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
	https://learnopengl.com/Lighting/Basic-Lighting

Ambient lighting: elighting constant that always gives the object some color.
Diffuse lighting: The more a part of an object faces the light source, the brighter it becomes.
Specular lighting: simulates the bright spot of a light that appears on shiny objects.

*/


/*
	a.a_colour = MRT_CYAN;
	a.l_colour = MRT_LIGHT_BLUE;
	a.sp_colour = MRT_YELLOW;

*/

/*
	Calculate the resulting colour from ambient and surface colour
*/
int	calculate_px_colour(t_app *a, float diff, int l_colour, float l_brightness , int obj_colour)
{
	// int	emission;
	int	ambient;
	int	diffuse;
	int	light_ambient;

	// (void)l_colour;
	// (void)l_brightness;
	(void)diff;

	ambient = colour_pallet_multiply(a->global_ambient, obj_colour);

	light_ambient = colour_brightness_multi(l_colour, l_brightness);
	diffuse = colour_pallet_multiply(l_colour, obj_colour);

	// if (diff > PI_HALF)
	// 	return (ambient);


	return (ambient);


	// return diffuse;

	// return MRT_PINK;

	// return colour_pallet_multiply(colour_pallet_add(obj_colour, colour_in_shadow), diffuse);

	// return colour_pallet_lerp(0, PI_HALF, angle, (t_v2int){obj_colour, colour_in_shadow});

}

/*
	To calculate the resulting colour is hard, so bare with me.

	This is the link that explains it all!
	https://learnopengl.com/Lighting/Basic-Lighting
*/
void	resulting_colour(t_app *a, t_v2int pix, t_v3 intersection, t_v3 center)
{
	t_v3	normal_of_intersection = v3_subtract(center, intersection);
	t_v3	vector_of_light = v3_subtract(a->l_origin, intersection);

	// float	theta = acosf(v3_dot(normal_of_intersection, vector_of_light)
	// 			/ (v3_mag(normal_of_intersection) * v3_mag(vector_of_light)));


	int		ambient = colour_pallet_multiply(a->global_ambient, a->sp_colour);

	t_v3	norm = v3_unitvec(normal_of_intersection);
	t_v3	light_dir = v3_unitvec(vector_of_light);

	float	diff = fmax(v3_dot(norm, light_dir), 0.0);
	int		diffuse = colour_brightness_multi(a->l_colour, diff);
	int		result = colour_pallet_multiply(colour_pallet_add(ambient, diffuse), a->sp_colour);

	wrapper_pixel_put(&a->img, pix.x, pix.y, result);
}
