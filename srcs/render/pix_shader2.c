/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_shader2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:22:31 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 16:24:51 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Compute diffuse color of i-th light at a certain point, given a point
	and the normal of the surface at that point.
*/
t_v3	get_light_diffuse(t_scene *s, int l_num, t_intersection *i)
{
	t_v3	light_dir;

	light_dir = v3_unitvec(v3_subtract(get_light(s, l_num)->position, i->poi));
	return (v3_multiply(get_light_colour(s, l_num),
			fmaxf(v3_dot(i->poi_normal, light_dir), 0.0)));
}

/*
	returns the light's colour attenuated by the intensity.
*/
t_v3	get_light_colour(t_scene *s, int l_num)
{
	return (v3_multiply(get_light(s, l_num)->colour,
			get_light(s, l_num)->ratio));
}
