/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:36:24 by znichola          #+#    #+#             */
/*   Updated: 2023/04/28 11:37:53 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3	get_light_diffuse(t_scene *s, int l_num, t_object *me, t_v3 poi, t_v3 norm);
static t_v3	get_light_colour(t_scene *s, int l_num);
static t_v3	get_light_specular(t_scene *s, int i, t_v3 poo, t_v3 poi, t_v3 poi_norm);
static t_object	*is_in_shadow(t_scene *s, t_object *me, t_v3 poo, int l_num);

//static t_v3	bmp_offset(t_scene *s, t_object *me, t_v3 norm, float strength);

/*
	We are following the workflow outlined for openGL in this article
	https://learnopengl.com/Lighting/Basic-Lighting

	If we follow the formula I think it's not quite right, the

*/
t_v3	pix_shader(t_scene *s, t_object *me, t_v3 poo, t_v3 poi)
{
	t_v3	obj_col;
	t_v3	ambiant;
	t_v3	diffuse;
	t_v3	specular;
	t_v3	poi_norm;

	//poi_norm = v3_unitvec(v3_subtract(get_obj_pos(me), poi)); // need to pass this to other functions for opti!
	poi_norm = get_poi_norm(me, poi);

	// poi_norm = bmp_offset(s, me, poi_norm, 1.0);

	obj_col = get_obj_emmision(me, poi);
	ambiant = v3_multiply(s->ambiant.colour, s->ambiant.ratio);
	diffuse = (t_v3){0.0f, 0.0f, 0.0f};
	specular = (t_v3){0.0f, 0.0f, 0.0f};

	int i = ft_lstsize(s->lights_list);
	while (--i >= 0)
	{
		if (!is_in_shadow(s, me, poi, i))
		{
			diffuse = col_add(get_light_diffuse(s, i, me, poi, poi_norm), diffuse);
			specular = col_add(col_scale(get_light_specular(s, i, poo, poi, poi_norm), get_light(s, i)->ratio), specular);
		}
	}

	// specular = ORIGIN; // uncomment to switch off spec component.
	// diffuse = ORIGIN;
	// ambiant = ORIGIN;
	// obj_col = (t_v3){1.0f, 1.0f, 1.0f};

	// return (col_multi(col_add(col_add(ambiant, diffuse), specular), obj_col));
	return (col_add(col_multi(col_add(ambiant, diffuse), obj_col), specular)); // I think this is correct but it's not how the openGL site explains it.
}

static t_v3	get_light_diffuse(t_scene *s, int l_num, t_object *me, t_v3 poi, t_v3 norm)
{
	t_v3	l_poi_norm;
	t_v3	me_poi_norm; // needs to be given as parameter!

	(void)me;
	// me_poi_norm = v3_unitvec(v3_subtract(get_obj_pos(me), poi));
	me_poi_norm = norm;
	l_poi_norm = v3_unitvec(v3_subtract(get_light(s, l_num)->position, poi));
	return (v3_multiply(get_light_colour(s, l_num),
		fmaxf(v3_dot(me_poi_norm, l_poi_norm), 0.0)));
}

/*
	returns the light's colour attenuated by the intesity.
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

	is this function used somewhere else? why is it not static?
*/
t_v3	reflection(t_v3 incident, t_v3 surface_normal)
{
	t_v3	foo = v3_multiply(surface_normal, 2.0 * v3_dot(incident, surface_normal));
	return (v3_unitvec(v3_subtract(incident, foo)));
}

/*
	compute the specular colour of the i-th light

	poo: is the point of origin
	poi: is the point of intersection
*/
static t_v3	get_light_specular(t_scene *s, int i, t_v3 poo, t_v3 poi, t_v3 poi_norm)
{
	static float	strength = 0.3;
	static float	exp = 128;
	float			spec;
	t_v3			view_norm_dir;
	t_v3			light_norm_dir;
	t_v3			reflection_dir;

	//poo is the  camera positon in this instance maybe this should be refactored
	//and dosn't need to be passed as it's alwyas the same variable. idk really.
	view_norm_dir = v3_unitvec(v3_subtract(poo, poi)); //sure it's good
	light_norm_dir = v3_unitvec(v3_subtract(poi, get_light(s, i)->position)); // inverting these flips the specular location
	reflection_dir = reflection(light_norm_dir, poi_norm);
	spec = powf(fmaxf(v3_dot(view_norm_dir, reflection_dir), 0), exp);
	return (col_scale(get_light(s, i)->colour, strength * spec));
}

static t_object	*is_in_shadow(t_scene *s, t_object *me, t_v3 poo, int l_num)
{
	t_list	*current;
	t_v3	light_norm_dir;
	t_v3	tmp;

	light_norm_dir = v3_unitvec(v3_subtract(get_light(s, l_num)->position, poo));
	current = s->objects_list;
	while (current)
	{
		if (current->content == me)
		{
			;// printf("it's me, don't check.");
		}
		else
		{
			if (get_obj_poi(current->content, light_norm_dir, poo, &tmp) < FLT_MAX)
				return (current->content);
		}
		current = current->next;
	}
	return (NULL);
}

// getting uv texture coordinates
// https://www.mvps.org/directx/articles/spheremap.htm
// http://raytracerchallenge.com/bonus/texture-mapping.html

/*
	calculates the new normal rsulting from the bmp deformation
*/
/*
static t_v3	bmp_offset(t_scene *s, t_object *me, t_v3 norm, float strength)
{
	float	tu;
	float	tv;

	(void)s;
	(void)me;
	tu = (((atan2f(norm.x, norm.z)) / (2 * M_PI)) + 0.5);
	tv = ((acosf(norm.y / 1)) / M_PI);

	return (v3_unitvec(v3_add(norm,
			v3_multiply(finite_diff(getset_app(NULL), tu, tv), strength)
			)));
}
*/
