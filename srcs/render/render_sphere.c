/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:28:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/14 11:33:21 by znichola         ###   ########.fr       */
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
	int viewport_offset = 300;

	/*
		The world and screen have a one to one relationship,
		one pixel is one unit in the world, and the camera is a 0,0,0.

		To calculate the plane to which we project the sphear we use the
		viewport_offset. Idk why, but is behind the sphere is a 80 vs 300,
		but otherwise it's too small??? who knows, we'll have to redo
		the camera anyways.
	*/
	for (int x = - a->img.width / 2; x < a->img.width; x++)
	{
		for (int y = - a->img.height / 2; y < a->img.height; y++)
		{
			/*
				We construct our vector for the current pixel of the view_port.
				as the camera is a 0,0,0 it's just the pixels coordinates,
				otherwise we would need to subtract the camera's vector with the
				viewports.
			*/
			t_v3 vec = (t_v3){x, y, viewport_offset};

			/*
				we normalise the vector so it's length is one unit, we are
				trying to find the point of intersection of this line and our
				sphere, if there is one.
			*/
			vec = v3_unitvec(vec);

			/*
				we calculate the distance between our camera and
				the circle's center, this is the magnetude of the vector w.
			*/
			t_v3 w = v3_subtract((t_v3){0, 0, 0}, a->circle);

			/*
				We are now trying to find the point t along the line w that
				intersects the sphere.

				||t*v + w|| ^ 2 = r ^ 2

				This expands to a quadratic equation with some math stuff:

				a = (v * v)
				b = 2(v * w)
				c = (w * w) - r ^ 2

				solve for t
				a * t ^ 2 + b * t + c = 0
			*/
			float _a = v3_dot(vec, vec);
			float _b = v3_dot(vec, w) *  2;
			float _c = v3_dot(w, w) - powf(a->radius, 2);

			/*
				Depending on the value of the discriminant we can tell if there
				will be an intersection with the sphere.
			*/
			float discriminant = pow(_b, 2) - 4 * _a * _c;

			/*
				there is an intersection, let's calculate it!
			*/
			if (discriminant > 0)
			{
				float dsquared = sqrt(pow(_b, 2) - 4 * _a * _c);
				float t1 = (-_b - dsquared) / (2 * _a);
				float t2 = (-_b + dsquared) / (2 * _a);

				if (t1 < t2)
					calculate_shadow(a, (t_v2int){x, y}, v3_multiply(vec, t1), a->circle);
				else
					wrapper_pixel_put(&a->img, x, y, MRT_PINK); //never happens
			}

			/*
				it intersects on the tangent, dosen't ever seem to happen.
			*/
			else if (discriminant == 0)
				wrapper_pixel_put(&a->img, x, y, MRT_LIGHT_BLUE);

			/*
				no intersection
			*/
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
	/*
		To calculate a new vector from two others we subtract them.
		For the normal we use the vector for the center of the sphere and
		the vector for the intersection.
	*/
	t_v3	normal_of_intersection = v3_subtract(center, intersection);

	/*
		Using the same method we find the vector from the light to the
		intersection.
	*/
	t_v3	vector_of_light = v3_subtract(a->light, intersection);

	/*
		To calculate the angle between the two vectors

		theta = acos( (n * l) / (|n| * |l|))
	*/
	float	theta = acosf(v3_dot(normal_of_intersection, vector_of_light)
				/ (v3_mag(normal_of_intersection) * v3_mag(vector_of_light)));
	if (theta < PI / 2)
		wrapper_pixel_put(&a->img, pix.x, pix.y, colour_lerp(0, PI / 2, theta));
	else
		wrapper_pixel_put(&a->img, pix.x, pix.y, MRT_BLACK);
}


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
