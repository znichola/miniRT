/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:28:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/14 00:01:58 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

// http://www.illusioncatalyst.com/notes_files/mathematics/line_sphere_intersection.php

void	render_sphere(t_app *a)
{
	int camera_offset = 200;

	for (int x = - a->img.width / 2; x < a->img.width; x++)
	{
		for (int y = - a->img.height / 2; y < a->img.height; y++)
		{
			t_v3 vec = (t_v3){x, y, camera_offset};
			vec = v3_unitvec(vec);
			t_v3 w = v3_subtract((t_v3){0, 0, 0}, a->circle);


			float _a = v3_dot(vec, vec);
			float _b = v3_dot(vec, w) *  2;
			float _c = v3_dot(w, w) - powf(a->radius, 2);

			float delta = pow(_b, 2) - 4 * _a * _c;


			if (delta > 0)
			{
				float dpow = sqrt(pow(_b, 2) - 4 * _a * _c);
				float t1 = (-_b - dpow) / (2 * _a);
				float t2 = (-_b + dpow) / (2 * _a);

				if (t1 < t2)
				{
					calculate_shadow(a, (t_v2int){x, y}, v3_multiply(vec, t1), a->circle);
				}
					// wrapper_pixel_put(&a->img, x, y, MRT_WHITE); // the closer intesection point is t1
				else
				{
					printf("sdfksd\n");

					wrapper_pixel_put(&a->img, x, y, MRT_GREY); // here it's t2 sometimes though it's not apparently
				}
			}
			else if (delta == 0)
				my_mlx_pixel_put(&a->img, x, y, MRT_LIGHT_BLUE);
			else
				; // point dosen't intersect
		}
	}
}


void	calculate_shadow(t_app *a, t_v2int pix, t_v3 intersection, t_v3 center)
{
	t_v3	normal_of_intersection = v3_subtract(center, intersection);
	t_v3	vector_of_light = v3_subtract(a->light, intersection);

	float	theta = acosf(v3_dot(normal_of_intersection, vector_of_light)
												/
							(v3_mag(normal_of_intersection) * v3_mag(vector_of_light)));
	if (theta < PI / 2)
	{
		wrapper_pixel_put(&a->img, pix.x, pix.y, colour_lerp(0, PI / 2, theta));
		// wrapper_pixel_put(&a->img, pix.x, pix.y, MRT_WHITE);
	}
	else
	{
		wrapper_pixel_put(&a->img, pix.x, pix.y, MRT_GREY);
	}
}

int	colour_lerp(float min, float max, float point)
{
	int		str_col;
	int		end_col;
	double	prct;

	str_col = MRT_WHITE;
	end_col = MRT_GREY;
	prct = (point - min) / (max - min);
	return (create_trgb(0,
			get_r(str_col) * (1 - prct) + get_r(end_col) * prct,
			get_g(str_col) * (1 - prct) + get_g(end_col) * prct,
			get_b(str_col) * (1 - prct) + get_b(end_col) * prct
		));
}
