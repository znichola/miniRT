/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:28:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/14 17:34:56 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

// http://www.illusioncatalyst.com/notes_files/mathematics/line_sphere_intersection.php
/*
	This link is great at explaining the steps and is what this
	calculation is based off.
*/

void	render_sphere(t_app *a)
{
	int viewport_offset = 400;

	for (int x = - a->img.width / 2; x < a->img.width; x++)
	{
		for (int y = - a->img.height / 2; y < a->img.height; y++)
		{
			t_v3 vec = (t_v3){x, y, viewport_offset};
			vec = v3_unitvec(vec);
			t_v3 w = v3_subtract((t_v3){0, 0, 0}, a->sp_origin);

			float _a = v3_dot(vec, vec);
			float _b = v3_dot(vec, w) *  2;
			float _c = v3_dot(w, w) - powf(a->sp_radius, 2);

			float discriminant = pow(_b, 2) - 4 * _a * _c;

			if (discriminant > 0)
			{
				float dsquared = sqrt(pow(_b, 2) - 4 * _a * _c);
				float t1 = (-_b - dsquared) / (2 * _a);
				float t2 = (-_b + dsquared) / (2 * _a);

				if (t1 < t2)
					calculate_shadow(a, (t_v2int){x, y}, v3_multiply(vec, t1), a->sp_origin);
				else
					wrapper_pixel_put(&a->img, x, y, MRT_PINK); //never happens
			}
			else
				wrapper_pixel_put(&a->img, x, y, MRT_BLACK);
		}
	}
}

/*
	To calculate the shadow we draw a vector from the surface of the sphere to
	the light source and compare the angle to normal at the intersection.
*/
void	calculate_shadow(t_app *a, t_v2int pix, t_v3 intersection, t_v3 center)
{
	t_v3	normal_of_intersection = v3_subtract(center, intersection);
	t_v3	vector_of_light = v3_subtract(a->l_origin, intersection);

	float	theta = acosf(v3_dot(normal_of_intersection, vector_of_light)
				/ (v3_mag(normal_of_intersection) * v3_mag(vector_of_light)));

	wrapper_pixel_put(&a->img, pix.x, pix.y,
	calculate_px_colour(a, theta, a->l_colour, a->l_brightness, a->sp_colour));
/*
	if (theta < PI / 2)
		wrapper_pixel_put(&a->img, pix.x, pix.y, colour_lerp(0, PI / 2, theta));
	else
		wrapper_pixel_put(&a->img, pix.x, pix.y, MRT_BLACK);
*/
}
