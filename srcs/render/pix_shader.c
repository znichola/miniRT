/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:36:24 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 22:01:52 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3		get_light_diffuse(t_scene *s, int l_num, t_v3 poi, t_v3 norm);
static t_v3		get_light_colour(t_scene *s, int l_num);
static t_v3		reflection(t_v3 incident, t_v3 surface_normal);
static t_v3		get_light_specular(t_scene *s, int i, t_v3 poi, t_v3 poi_norm);
static t_object	*is_in_shadow(t_scene *s, t_object *me, t_v3 poo, int l_num);

//static t_v3	bmp_offset(t_scene *s, t_object *me, t_v3 norm, float strength);

/*
	We are following the workflow outlined for openGL in this article
	https://learnopengl.com/Lighting/Basic-Lighting
*/
t_v3	pix_shader(t_scene *s, t_object *me, t_intersection *in)
{
	t_v3	obj_col;
	t_v3	ambiant;
	t_v3	diffuse;
	t_v3	specular;
	t_v3	poi_norm;

	t_v3	poi = in->poi; /* tmp compatability shit */

	// poi_norm = bmp_offset(s, me, poi_norm, 1.0);
	poi_norm = get_poi_norm(me, in);
	obj_col = get_obj_emmision(me, in);
	ambiant = v3_multiply(s->ambiant.colour, s->ambiant.ratio);
	diffuse = (t_v3){0.0f, 0.0f, 0.0f};
	specular = (t_v3){0.0f, 0.0f, 0.0f};

	int i = ft_lstsize(s->lights_list);
	while (--i >= 0)
	{
		if (!is_in_shadow(s, me, poi, i))
		{
			diffuse = col_add(get_light_diffuse(s, i, poi, poi_norm), diffuse);
			specular = col_add(col_scale(get_light_specular(s, i, poi, poi_norm), get_light(s, i)->ratio), specular);
		}
	}

	/* I think this is correct but it's not how the openGL site explains it.*/
	return (col_add(col_multi(col_add(ambiant, diffuse), obj_col), specular));
}

/*
	Compute diffuse color of i-th light at a certain point, given a point
	and the normal of the surface at that point.
*/
static t_v3	get_light_diffuse(t_scene *s, int l_num, t_v3 point, t_v3 norm)
{
	t_v3	light_dir;

	light_dir = v3_unitvec(v3_subtract(get_light(s, l_num)->position, point));
	return (v3_multiply(get_light_colour(s, l_num),
				fmaxf(v3_dot(norm, light_dir), 0.0)));
}

/*
	returns the light's colour attenuated by the intensity.
*/
static t_v3	get_light_colour(t_scene *s, int l_num)
{
	return (v3_multiply(get_light(s, l_num)->colour,
						get_light(s, l_num)->ratio));
}

/*
	Compute the reflection direction, given an incident vector and the surface
	normal.
*/
static t_v3	reflection(t_v3 incident, t_v3 surface_normal)
{
	t_v3	foo = v3_multiply(surface_normal, 2.0 * v3_dot(incident, surface_normal));
	return (v3_unitvec(v3_subtract(incident, foo)));
}

/*
	compute the specular colour of the i-th light

	poi: is the point of intersection
*/
static t_v3	get_light_specular(t_scene *s, int i, t_v3 poi, t_v3 poi_norm)
{
	static float	strength = 0.3;
	static float	exp = 128;
	float			spec;
	t_v3			view_norm_dir;
	t_v3			light_norm_dir;
	t_v3			reflection_dir;

	view_norm_dir = v3_unitvec(v3_subtract(s->camera.position, poi));
	light_norm_dir = v3_unitvec(v3_subtract(poi, get_light(s, i)->position));
	reflection_dir = reflection(light_norm_dir, poi_norm);
	spec = powf(fmaxf(v3_dot(view_norm_dir, reflection_dir), 0), exp);
	return (col_scale(get_light(s, i)->colour, strength * spec));
}

/*
	Check if there is an object between the l_num-th light source and a given
	point on an object.
	Return a pointer to that object or NULL.
*/
static t_object	*is_in_shadow(t_scene *s, t_object *me, t_v3 point, int l_num)
{
	t_list			*current;
	t_v3			light_dir;
	t_intersection	tmp;
	float			dist;

	light_dir = v3_unitvec(v3_subtract(get_light(s, l_num)->position, point));
	current = s->objects_list;
	while (current)
	{
		if (current->content != me)
		{
			dist = get_obj_poi(current->content, light_dir, point, &tmp);
			if (dist < FLT_MAX)
				return (current->content);
		}
		current = current->next;
	}
	return (NULL);
}

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
