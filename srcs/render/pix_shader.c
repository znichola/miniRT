/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:36:24 by znichola          #+#    #+#             */
/*   Updated: 2023/03/23 12:12:19 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3	get_light_diffuse(t_scene *s, t_object *me, t_v3 poi);
static t_v3	get_light_colour(t_scene *s, int l_num);


/*
	We are following the workflow outlined for openGL in this article
	https://learnopengl.com/Lighting/Basic-Lighting
*/
t_v3	pix_shader(t_scene *s, t_object *me, t_v3 *poi)
{
	t_v3	obj_col;
	t_v3	ambiant;
	t_v3	diffuse;

	obj_col = get_obj_emmision(me, *poi);
	ambiant = v3_multiply(s->ambiant.colour, s->ambiant.ratio);
	diffuse = get_light_diffuse(s, me, *poi);
	return (col_multi(col_add(ambiant, diffuse), obj_col));
}

t_v3	get_light_diffuse(t_scene *s, t_object *me, t_v3 poi)
{
	t_v3	light_poi_unitvec;
	t_v3	me_poi_unitvec;

	me_poi_unitvec = v3_unitvec(v3_subtract(get_obj_pos(me), poi));
	light_poi_unitvec = v3_unitvec(v3_subtract(poi, get_light(s, 0)->position));
	return (v3_multiply(get_light_colour(s, 0),
		fmaxf(v3_dot(me_poi_unitvec, light_poi_unitvec), 0.0)));
}

static t_v3	get_light_colour(t_scene *s, int l_num)
{
	return (v3_multiply(get_light(s, l_num)->colour,
						get_light(s, l_num)->ratio));
}
