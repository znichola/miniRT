/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:36:24 by znichola          #+#    #+#             */
/*   Updated: 2023/03/23 19:40:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3	get_light_diffuse(t_scene *s, int l_num, t_object *me, t_v3 poi);
static t_v3	get_light_colour(t_scene *s, int l_num);
static t_v3	get_light_specular(t_scene *s, t_v3 poo, t_v3 poi, t_v3 poi_norm);


/*
	We are following the workflow outlined for openGL in this article
	https://learnopengl.com/Lighting/Basic-Lighting
*/
t_v3	pix_shader(t_scene *s, t_object *me, t_v3 poo, t_v3 poi)
{
	t_v3	obj_col;
	t_v3	ambiant;
	t_v3	diffuse;
	t_v3	specular;
	t_v3	poi_norm;

	poi_norm = v3_unitvec(v3_subtract(get_obj_pos(me), poi)); // need to pass this to other functions for opti!
	obj_col = get_obj_emmision(me, poi);
	ambiant = v3_multiply(s->ambiant.colour, s->ambiant.ratio);
	diffuse = get_light_diffuse(s, 0, me, poi);
	diffuse = ORIGIN;
	specular = get_light_specular(s, poo, poi, poi_norm);
	// specular = ORIGIN;
	return (col_multi(col_add(col_add(ambiant, diffuse), specular), obj_col));
	// return ((t_v3){0,1,1});
}

t_v3	get_light_diffuse(t_scene *s, int l_num, t_object *me, t_v3 poi)
{
	t_v3	l_poi_norm;
	t_v3	me_poi_norm;

	me_poi_norm = v3_unitvec(v3_subtract(get_obj_pos(me), poi));
	l_poi_norm = v3_unitvec(v3_subtract(poi, get_light(s, l_num)->position));
	return (v3_multiply(get_light_colour(s, l_num),
		fmaxf(v3_dot(me_poi_norm, l_poi_norm), 0.0)));
}

/*
	returns the light's colour attenuated via the intesity.
*/
static t_v3	get_light_colour(t_scene *s, int l_num)
{
	return (v3_multiply(get_light(s, l_num)->colour,
						get_light(s, l_num)->ratio));
}


/*
	I - 2.0 * dot(N, I) * N.

	For a given incident vector I and surface normal N reflect returns the reflection direction calculated as I - 2.0 * dot(N, I) * N.
	N should be normalized in order to achieve the desired result.

	https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
*/
t_v3	reflection(t_v3 incident, t_v3 surface_normal)
{
	t_v3	foo = v3_multiply(surface_normal, 2.0 * v3_dot(incident, surface_normal));
	return (v3_unitvec(v3_subtract(incident, foo)));
}

/*
	return the specular
	poo: is the point of origin
	poi: is the point of intersection
*/
static t_v3	get_light_specular(t_scene *s, t_v3 poo, t_v3 poi, t_v3 poi_norm)
{
	float	spec;
	float	strength;
	float	epx;
	t_v3	light_norm;
	t_v3	view_norm;

	strength = .8;
	epx = 32;

	view_norm = v3_unitvec(v3_subtract(poo, poi));
	light_norm = v3_unitvec(v3_subtract(poi, get_light(s, 0)->position));

	t_v3	reflection_dir = reflection(light_norm, view_norm);
	spec = powf(fmaxf(v3_dot(view_norm, reflection_dir), 0), epx);
	return (v3_multiply(get_light(s, 0)->colour, strength * spec));
}
