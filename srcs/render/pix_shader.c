/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:36:24 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 22:22:30 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3		get_light_diffuse(t_scene *s, int l_num, t_intersection *i);
static t_v3		get_light_colour(t_scene *s, int l_num);
static t_v3		reflection(t_v3 incident, t_v3 surface_normal);
static t_v3	get_light_specular(t_scene *s, int n, t_intersection *i);
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

	obj_col = get_obj_emmision(me, in);
	ambiant = v3_multiply(s->ambiant.colour, s->ambiant.ratio);
	diffuse = (t_v3){0.0f, 0.0f, 0.0f};
	specular = (t_v3){0.0f, 0.0f, 0.0f};

	in->poi_bmp_normal = get_poi_norm(me, in);

	int i = ft_lstsize(s->lights_list);
	while (--i >= 0)
	{
		if (!is_in_shadow(s, me, in->poi, i))
		{
			diffuse = col_add(get_light_diffuse(s, i, in), diffuse);
			specular = col_add(col_scale(get_light_specular(s, i, in), get_light(s, i)->ratio), specular);
		}
	}

	/* I think this is correct but it's not how the openGL site explains it.*/
	return (col_add(col_multi(col_add(ambiant, diffuse), obj_col), specular));
}

/*
	Compute diffuse color of i-th light at a certain point, given a point
	and the normal of the surface at that point.
*/
static t_v3	get_light_diffuse(t_scene *s, int l_num, t_intersection *i)
{
	t_v3	light_dir;

	light_dir = v3_unitvec(v3_subtract(get_light(s, l_num)->position, i->poi));
	// light_dir = v3_add(light_dir, i->poi_bmp_normal);
	// light_dir = i->poi_normal;
	return (v3_multiply(get_light_colour(s, l_num),
				fmaxf(v3_dot(i->poi_normal, light_dir), 0.0)));
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
static t_v3	get_light_specular(t_scene *s, int n, t_intersection *i)
{
	static float	strength = 0.3;
	static float	exp = 128;
	float			spec;
	t_v3			view_norm_dir;
	t_v3			light_norm_dir;
	t_v3			reflection_dir;

	// view_norm_dir = v3_add(i->poi, i->poi_bmp_normal);
	view_norm_dir = v3_unitvec(v3_subtract(s->camera.position, i->poi));
	view_norm_dir = i->poi_normal;
	light_norm_dir = v3_unitvec(v3_subtract(i->poi, get_light(s, n)->position));
	reflection_dir = reflection(light_norm_dir, i->poi_normal);
	spec = powf(fmaxf(v3_dot(view_norm_dir, reflection_dir), 0), exp);
	return (col_scale(get_light(s, n)->colour, strength * spec));
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
// static t_v3	bmp_offset(t_scene *s, t_object *me, t_v3 norm, float strength)
// {
// 	t_v3	u;
// 	t_v3	v;
// 	t_v3	p;

// 	p = get_adjacent_pixels(texture, map, &u, &v);

// 	return (v3_unitvec(v3_add(norm,
// 			v3_multiply(v3_unitvec((t_v3){dx, dy, 255}), strength)
// 			)));
// }
