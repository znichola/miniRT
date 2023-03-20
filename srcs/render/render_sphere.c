/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:28:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/20 23:12:04 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <float.h>

// http://www.illusioncatalyst.com/notes_files/mathematics/line_sphere_intersection.php
/*
	This link is great at explaining the steps and is what this
	calculation is based off.
*/

void	render_sphere(t_app *a)
{
	for (int x = - a->img.width / 2; x < a->img.width / 2; x++)
	{
		for (int y = - a->img.height / 2; y < a->img.height / 2; y++)
		{
			// viewport calculation
			float	wr = tanf(a->c_fov / 2) * x;
			float	hr = tanf((a->c_fov / 2) * a->c_aspect_ratio) * y;

			t_v3	e = v3_add(a->c_origin, a->c_normal);
			t_v3	xdir = v3_unitvec(v3_cross(a->c_normal, (t_v3){0.0, 1.0, 0.0}));
			t_v3	ydir = v3_unitvec(v3_cross(a->c_normal, (t_v3){-1.0, 0.0, 0.0}));
			// t_v3	n = v3_cross(v3_unitvec(e), a->c_normal);

			xdir = v3_multiply(xdir, wr);
			ydir = v3_multiply(ydir, hr);

			t_v3	p = v3_add(xdir, ydir);

			t_v3	vec = v3_add(e, p);

			// vec = (t_v3){x, y, 1600};
			// vec = v3_unitvec(vec);

			// render the sphere
			t_v3 w = v3_subtract((t_v3){0, 0, 0}, a->sp_origin);
			// t_v3 w = v3_subtract(a->c_origin, a->sp_origin);
			float _a = v3_dot(vec, vec);
			float _b = v3_dot(vec, w) *  2;
			float _c = v3_dot(w, w) - powf(a->sp_radius, 2);
			float discriminant = pow(_b, 2) - 4 * _a * _c;

			if (discriminant > FLT_EPSILON)
			{
				float dsquared = sqrt(pow(_b, 2) - 4 * _a * _c);
				float t1 = (-_b - dsquared) / (2 * _a);
				float t2 = (-_b + dsquared) / (2 * _a);

				if (t1 < t2)
					resulting_colour(a, (t_v2int){x, y}, v3_multiply(vec, t1), a->sp_origin);
				else
					wrapper_pixel_put(&a->img, x, y, MRT_PINK); //never happens
			}
			else
				wrapper_pixel_put(&a->img, x, y, MRT_BLACK);
		}
	}
}


// void	render_sphere(t_app *a)
// {
// 	int viewport_offset = 1800;
// 	for (int x = - a->img.width / 2; x < a->img.width / 2; x++)
// 	{
// 		for (int y = - a->img.height / 2; y < a->img.height / 2; y++)
// 		{
// 			t_v3 vec = (t_v3){x, y, viewport_offset};
// 			vec = v3_unitvec(vec);
// 			t_v3 w = v3_subtract((t_v3){0, 0, 0}, a->sp_origin);

// 			float _a = v3_dot(vec, vec);
// 			float _b = v3_dot(vec, w) *  2;
// 			float _c = v3_dot(w, w) - powf(a->sp_radius, 2);

// 			float discriminant = pow(_b, 2) - 4 * _a * _c;

// 			if (discriminant > 0)
// 			{
// 				float dsquared = sqrt(pow(_b, 2) - 4 * _a * _c);
// 				float t1 = (-_b - dsquared) / (2 * _a);
// 				float t2 = (-_b + dsquared) / (2 * _a);

// 				if (t1 < t2)
// 					resulting_colour(a, (t_v2int){x, y}, v3_multiply(vec, t1), a->sp_origin);
// 				else
// 					wrapper_pixel_put(&a->img, x, y, MRT_PINK); //never happens
// 			}
// 			else
// 				wrapper_pixel_put(&a->img, x, y, MRT_BLACK);
// 		}
// 	}
// }


// /*
// 	To calculate the shadow we draw a vector from the surface of the sphere to
// 	the light source and compare the angle to normal at the intersection.
// */
// void	calculate_shadow(t_app *a, t_v2int pix, t_v3 intersection, t_v3 center)
// {
// 	t_v3	normal_of_intersection = v3_subtract(center, intersection);
// 	t_v3	vector_of_light = v3_subtract(a->l_origin, intersection);

// 	float	theta = acosf(v3_dot(normal_of_intersection, vector_of_light)
// 				/ (v3_mag(normal_of_intersection) * v3_mag(vector_of_light)));

// 	wrapper_pixel_put(&a->img, pix.x, pix.y,
// 	calculate_px_colour(a, theta, a->l_colour, a->l_brightness, a->sp_colour));
// /*
// 	if (theta < PI / 2)
// 		wrapper_pixel_put(&a->img, pix.x, pix.y, colour_lerp(0, PI / 2, theta));
// 	else
// 		wrapper_pixel_put(&a->img, pix.x, pix.y, MRT_BLACK);
// */
// }

/*
	To calculate the shadow we draw a vector from the surface of the sphere to
	the light source and compare the angle to normal at the intersection.
*/
void	calculate_shadow2(t_app *a, t_v2int pix, t_v3 intersection, t_v3 center)
{
	t_v3	normal_of_intersection = v3_subtract(center, intersection);
	t_v3	vector_of_light = v3_subtract(a->l_origin, intersection);

	float	theta = fmax(v3_dot(normal_of_intersection, vector_of_light), 0.0);

	wrapper_pixel_put(&a->img, pix.x, pix.y,
	calculate_px_colour(a, theta, a->l_colour, a->l_brightness, a->sp_colour));
/*
	if (theta < PI / 2)
		wrapper_pixel_put(&a->img, pix.x, pix.y, colour_lerp(0, PI / 2, theta));
	else
		wrapper_pixel_put(&a->img, pix.x, pix.y, MRT_BLACK);
*/
}
