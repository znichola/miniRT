/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:52:49 by znichola          #+#    #+#             */
/*   Updated: 2023/03/28 12:06:03 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	get_angle(t_v3 norm, t_v3 obj);

/*
	https://www.paulsprojects.net/tutorials/simplebump/simplebump.html

	The red book defines the standard OpenGL lighting equation as:

	Vertex Color = emission + globalAmbient + sum(attenuation * spotlight *
[lightAmbient + (max {L.N, 0} * diffuse) + (mrax {H.N, 0} ^ shininess)*specula])

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
	Calculate the resulting colour from ambient and surface colour
	~ depriciated ~
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

	// so we can modify the colour with the texture
	int		point_colour = a->sp_colour;


	// emmision colour
	t_v3	norm = v3_unitvec(normal_of_intersection);
	t_v3	light_dir = v3_unitvec(vector_of_light);


	// getting uv texture coordinates
	// https://www.mvps.org/directx/articles/spheremap.htm
	// http://raytracerchallenge.com/bonus/texture-mapping.html

	float	theta = atan2f(norm.x, norm.z);
	float	phi = acosf(norm.y / 1);

	float	raw_u = theta / (2 * M_PI);

	float	tu = (raw_u + 0.5);
	float	tv = (phi / M_PI);


	// // texture map
	int		texture_colour = earth_texture(a, tu * (3072), tv * (1536));
	// point_colour = colour_pallet_multiply(point_colour, texture_colour);
	point_colour = texture_colour;

	// bmp map
	norm =  v3_unitvec(v3_add(norm, v3_multiply(finite_diff(a, tu, tv), 3)));

	// ambient light
	int		ambient = colour_pallet_multiply(a->global_ambient, point_colour);
	// with night sky
	// ambient = colour_pallet_add(ambient, earth_nightlight_texture(a, tu * (3072), tv * (1536))); // I think addtion is not quite totally right, also the ambient shader isn't the best choice as it' still visible in the daytime.

	float	diff = fmax(v3_dot(norm, light_dir), 0.0);
	int		diffuse = colour_brightness_multi(a->l_colour, diff);

	// old ambient
	// int		ambient = colour_pallet_multiply(a->global_ambient, point_colour);

	// specular lighting
	// t_v3	view_pos = {0, 0, 0};
	t_v3	view_pos = a->c_origin;
	float	specular_strength = 0.8;

	t_v3	view_dir = v3_unitvec(v3_subtract(view_pos, intersection));
	// t_v3	reflect_dir = reflection(v3_multiply(light_dir, -1), norm);
	t_v3	reflect_dir = reflection(light_dir, norm);

	float	spec = powf(fmax(v3_dot(view_dir, reflect_dir), 0.0), 256);
	int		specular_colour = colour_brightness_multi(a->l_colour, specular_strength * spec);

	int		result = colour_pallet_multiply(colour_pallet_add(colour_pallet_add(ambient, diffuse), specular_colour), point_colour);


	// display pixel
	wrapper_pixel_put(&a->img, pix.x, pix.y, result);
}

/*
	I - 2.0 * dot(N, I) * N.

	For a given incident vector I and surface normal N reflect returns the reflection direction calculated as I - 2.0 * dot(N, I) * N.
	N should be normalized in order to achieve the desired result.

	https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
*/
// t_v3	reflection(t_v3 incident, t_v3 surface_normal)
// {
// 	t_v3	foo = v3_multiply(surface_normal, 2.0 * v3_dot(incident, surface_normal));
// 	return (v3_unitvec(v3_subtract(incident, foo)));
// }


float	get_angle(t_v3 norm, t_v3 obj)
{
	float	dot;
	float	angle;

	dot = v3_dot(norm, obj);
	angle = acos(dot);
	return (angle / (M_PI));
}

t_v3	finite_diff(t_app *a, float tu, float tv)
{
	int	u = tu * (3072);
	int	v = tv * (1536);
	// u *= 3072;
	// v *= 1536;
	// int	x0 = get_r(earth_bmp_texture(a, u - 1, v));
	int	x1 = get_r(earth_bmp_texture(a, u, v));
	int	x2 = get_r(earth_bmp_texture(a, u - 1, v));

	int	dx = (x1 - x2);
	int	dy = (get_r(earth_bmp_texture(a, u, v)) - get_r(earth_bmp_texture(a, u, v - 1)));
	return (v3_unitvec((t_v3){dx, dy, 255}));
}
