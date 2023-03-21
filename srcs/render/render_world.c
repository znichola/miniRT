/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:24:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/22 17:34:56 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <float.h>

static t_v3	pixel_to_ray(t_app *a, t_v2int pix);
static void	draw_ray(t_app *a, t_v3 ray);
static int	list_obj_type(t_list *obj);
static void	*list_obj_content(t_list *obj);

void	render_world(t_app *a)
{
	int		u;
	int		v;
	t_v3	ray;

	u = - a->img.width / 2;
	v = - a->img.height / 2;
	while (u < a->img.width / 2)
	{
		while (v < a->img.height / 2)
		{
			ray = pixel_to_ray(a, (t_v2int){u, v});
			draw_ray(a, ray);
			v++;
		}
		u++;
	}
}

static t_v3	pixel_to_ray(t_app *a, t_v2int pix)
{
	float	wr;
	float	hr;
	t_v3	e;
	t_v3	xdir;
	t_v3	ydir;

	wr = tanf(a->s.camera.fov / 2) * pix.x;
	hr = tanf((a->s.camera.fov / 2) * (a->img.width / a->img.height)) * pix.y;
	e = v3_add(a->s.camera.position, a->s.camera.orientation);
	xdir = v3_unitvec(v3_cross(a->s.camera.orientation, (t_v3){0,1,0}));
	ydir = v3_unitvec(v3_cross(a->s.camera.orientation, (t_v3){-1,0,0}));
	xdir = v3_multiply(xdir, wr);
	ydir = v3_multiply(ydir, hr);
	return (v3_add(e, v3_add(xdir, ydir)));
}

static void	draw_ray(t_app *a, t_v3 ray)
{
	//given a ray, compute the color of the associated pixel?
	t_object	*closest;
	t_v3		poi;
	t_v3		col;

	closest = find_poi(a, ray, a->s.camera.position, &poi);
	col = pix_shader(&a->s, closest, &poi);
}

t_v3	pix_shader(t_scene *s, t_object *me, t_v3 *poi)
{
	t_v3	col;
	t_v3	poi_normal;
	t_v3	light_ray;

	// poi_norm = v3_subtract()
	// get_light(s->lights_list)->position
}

/*
	poi means: "point of intersection"
*/
t_object	*find_poi(t_app *a, t_v3 ray, t_v3 origin, t_v3 *poi)
{
	t_list		*current;
	t_object	*closest;
	float		closest_dist;
	float		dist;

	closest = NULL;
	closest_dist = FLT_MAX;
	current = a->s.objects_list;
	while (current)
	{
		if (list_obj_type(current) == e_sphere)
		{
			dist = poi_sphere(list_obj_content(current), ray, origin, poi);
		}
		else if (list_obj_type(current) == e_plane)
		{
			dist = FLT_MAX /*plane*/;
		}
		else if (list_obj_type(current) == e_cylinder)
		{
			dist = FLT_MAX /*cylinder*/;
		}
		else
		{
			dist = FLT_MAX /*pass*/;
		}
		if (dist != FLT_MAX && dist < closest_dist)
		{
			closest_dist = dist;
			closest = current->content;
		}
		current = current->next;
	}
	return (closest);
}

static int	list_obj_type(t_list *obj)
{
	return (((t_object *)obj->content)->type);
}

static void	*list_obj_content(t_list *obj)
{
	if (list_obj_type(obj) == e_sphere)
		return (&((t_object *)obj->content)->object.sp);
	if (list_obj_type(obj) == e_cylinder)
		return (&((t_object *)obj->content)->object.cy);
	if (list_obj_type(obj) == e_plane)
		return (&((t_object *)obj->content)->object.pl);
	return (0);
}

t_light	*get_light(t_list *l)
{
	return ((t_light *)(l->content));
}

t_v3	get_pos(t_object *obj)
{

}
