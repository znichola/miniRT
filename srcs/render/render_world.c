/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:24:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/22 18:42:14 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <float.h>

static t_v3	pixel_to_ray(t_app *a, t_v2int pix);
static t_v3	draw_ray(t_app *a, t_v3 ray);
static int	list_obj_type(t_list *obj);
static void	*list_obj_content(t_list *obj);

t_v3	get_obj_emmision(t_object *obj, t_v3 poi);
t_v3	get_obj_pos(t_object *obj);
float	get_obj_lightfactor(t_scene *s, t_object *me, t_v3 poi);
t_object	*find_poi(t_app *a, t_v3 ray, t_v3 origin, t_v3 *poi);
t_v3	pix_shader(t_scene *s, t_object *me, t_v3 *poi);
t_light	*get_light(t_scene *s, int num);

int	render_world(t_app *a)
{
	int		u;
	int		v;
	t_v3	ray;
	t_v3	clr;

	u = - a->img.width / 2;
	v = - a->img.height / 2;
	while (u < a->img.width / 2)
	{
		while (v < a->img.height / 2)
		{
			ray = pixel_to_ray(a, (t_v2int){u, v});
			clr = draw_ray(a, ray);
			wrapper_pixel_put(&a->img, u, v, v3_to_col(clr));
			v++;
		}
		u++;
	}
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
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

static t_v3	draw_ray(t_app *a, t_v3 ray)
{
	//given a ray, compute the color of the associated pixel?
	t_object	*closest;
	t_v3		poi;
	t_v3		col;

	closest = find_poi(a, ray, a->s.camera.position, &poi);
	if (closest)
		col = pix_shader(&a->s, closest, &poi);
	else
		col = (t_v3){0,0,0};
	return (col);
}

t_v3	pix_shader(t_scene *s, t_object *me, t_v3 *poi)
{
	t_v3	emission;
	t_v3	ambiant;
	t_v3	normal_of_intersection;
	float	light_factor;

	emission = get_obj_emmision(me, *poi);
	ambiant = v3_multiply(s->ambiant.colour, s->ambiant.ratio);
	normal_of_intersection = v3_subtract(get_obj_pos(me), *poi);
	light_factor = get_obj_lightfactor(s, me, *poi);
	return (col_multi(
		v3_multiply(ambiant, 1 - light_factor),
		emission));
}

float	get_obj_lightfactor(t_scene *s, t_object *me, t_v3 poi)
{
	t_v3	light_poi_unitvec;
	t_v3	me_poi_unitvec;

	me_poi_unitvec = v3_unitvec(v3_subtract(get_obj_pos(me), poi));
	light_poi_unitvec = v3_unitvec(v3_subtract(poi, get_light(s, 0)->position));
	return (fmaxf(v3_dot(me_poi_unitvec, light_poi_unitvec), 0.0));
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

t_light	*get_light(t_scene *s, int num)
{
	t_list *current;
	int	i;

	current = s->lights_list;
	i = 0;
	while (current)
	{
		if (i == num)
		{
			return (current->content);
		}
		current = current->next;
		i++;
	}
	printf("GET_LIGHT CHAOS: num: %d\n", num);
	return (NULL);
}

t_v3	get_obj_pos(t_object *obj)
{
	//later;
	(void)obj;
	return ((t_v3){0,0,42});
}

t_v3	get_sp_emmision(t_object *me, t_v3 poi)
{
	t_sphere sp;
	(void)me;
	(void)poi;
	sp = me->object.sp;
	return (sp.colour);
}

t_v3	get_cy_emmision(t_cylinder *me, t_v3 poi)
{
	(void)me;
	(void)poi;
	return (me->colour);
}

t_v3	get_pl_emmision(t_cylinder *me, t_v3 poi)
{
	(void)me;
	(void)poi;
	return (me->colour);
}

t_v3	get_emmision_passthrough(t_object *me, t_v3 poi)
{
	(void)me;
	printf("can't get an emmision from this type of object\n");
	return (poi);
}


t_v3	get_obj_emmision(t_object *obj, t_v3 poi)
{
	t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_v3)  = {
		get_emmision_passthrough,
		get_emmision_passthrough,
		get_emmision_passthrough,
		get_sp_emmision,
		get_emmision_passthrough,
		get_emmision_passthrough};

	if (obj->type < 0 || obj->type  >= MRT_NUM_OBJ_TYPES)
		return (get_emmision_passthrough(obj, poi));
	return (f[obj->type](obj, poi));
}