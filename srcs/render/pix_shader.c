/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:36:24 by znichola          #+#    #+#             */
/*   Updated: 2023/03/25 15:40:32 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3	get_light_diffuse(t_scene *s, int l_num, t_object *me, t_v3 poi);
static t_v3	get_light_colour(t_scene *s, int l_num);
static t_v3	get_light_specular(t_scene *s, t_v3 poo, t_v3 poi, t_v3 poi_norm);
static int	is_in_shadow(t_scene *s, t_object *me, t_v3 poo, int l_num);


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

	poi_norm = v3_unitvec(v3_subtract(get_obj_pos(me), poi)); // need to pass this to other functions for opti!
	obj_col = get_obj_emmision(me, poi);
	ambiant = v3_multiply(s->ambiant.colour, s->ambiant.ratio);

	// if (is_in_shadow(s, me, poi, 0))
	// {
	// 	// printf("test\n");
	// 	return (col_multi(ambiant, obj_col));
	// 	return (COL_PINK);
	// }
	// else
	// {
		diffuse = get_light_diffuse(s, 0, me, poi);
		specular = col_scale(get_light_specular(s, poo, poi, poi_norm), get_light(s, 0)->ratio);
		// specular = get_light_specular(s, poo, poi, poi_norm);
	// }

	// specular = ORIGIN; // uncomment to switch off spec component.
	// diffuse = ORIGIN;
	// ambiant = ORIGIN;
	// obj_col = (t_v3){1.0f, 1.0f, 1.0f};

	// return (col_multi(col_add(col_add(ambiant, diffuse), specular), obj_col));
	return (col_add(col_multi(col_add(ambiant, diffuse), obj_col), specular)); // I think this is correct but it's not how the openGL site explains it.
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
*/
t_v3	reflection(t_v3 incident, t_v3 surface_normal)
{
	t_v3	foo = v3_multiply(surface_normal, 2.0 * v3_dot(incident, surface_normal));
	return (v3_unitvec(v3_subtract(incident, foo)));
}

/*
	return the specular colour
	poo: is the point of origin
	poi: is the point of intersection
*/
static t_v3	get_light_specular(t_scene *s, t_v3 poo, t_v3 poi, t_v3 poi_norm)
{
	static float	strength = 0.3;
	static float	epx = 128;
	float	spec;
	t_v3	view_norm_dir;
	t_v3	light_norm_dir;

	//poo is the  camera positon in this instance maybe this should be refactored
	//and dosn't need to be passed as it's alwyas the same variable. idk really.
	view_norm_dir = v3_unitvec(v3_subtract(poo, poi)); //sure it's good
	light_norm_dir = v3_unitvec(v3_subtract(poi, get_light(s, 0)->position)); // inverting these flips the specular location

	t_v3	reflection_dir = reflection(light_norm_dir, poi_norm);
	spec = powf(fmaxf(v3_dot(view_norm_dir, reflection_dir), 0), epx);

	// printf("%.3f\n", fmaxf(v3_dot(view_norm, reflection_dir), 0), epx);
	// print_v3("reflection\n", &reflection_dir);
	// print_v3("col", col_scale(get_light(s, 0)->colour, strength * spec));
	return (col_scale(get_light(s, 0)->colour, strength * spec));


	// return ((t_v3){0,0,0});
	// return ((t_v3){0.2, .2, .13});
}

static int	is_in_shadow(t_scene *s, t_object *me, t_v3 poo, int l_num)
{
	t_list	*current;
	t_v3	light_norm_dir;
	t_v3	tmp;

	light_norm_dir = v3_unitvec(v3_subtract(poo, get_light(s, l_num)->position));
	// light_norm_dir = v3_unitvec(v3_subtract(get_light(s, l_num)->position, poo));
	current = s->objects_list;
	while(current)
	{
		if (current->content == me)
		{
			;// printf("it's me, don't check.");
		}
		else
		{
			if (get_obj_poi(current->content, light_norm_dir, poo, &tmp) < FLT_MAX)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
