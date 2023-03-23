/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:24:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/23 01:19:25 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <float.h>

static t_v3	pixel_to_ray(t_app *a, int u, int v);
static t_v3	draw_ray(t_app *a, t_v3 ray);
static int	list_obj_type(t_list *obj);
static void	*list_obj_content(t_list *obj);

t_v3	get_obj_emmision(t_object *obj, t_v3 poi);
t_v3	get_obj_pos(t_object *obj);
float	get_obj_lightfactor(t_scene *s, t_object *me, t_v3 poi);
float	get_obj_poi(t_object *obj, t_v3 ray, t_v3 source, t_v3 *poi);

t_object	*find_poi(t_app *a, t_v3 ray, t_v3 origin, t_v3 *poi);
t_v3	pix_shader(t_scene *s, t_object *me, t_v3 *poi);
t_light	*get_light(t_scene *s, int num);

int	render_world(t_app *a)
{
	int		u;
	int		v;
	t_v3	ray;
	t_v3	clr;

	if (!assign_keybinds(a))
		return (0);

	u = 0;
	while (u < a->img.width)
	{
		v = 0;
		while (v < a->img.height)
		{
			ray = pixel_to_ray(a, u, v);
			clr = draw_ray(a, ray);
			wrapper_pixel_put(&a->img, u, v, v3_to_col(clr));
			v++;
		}
		// printf("\n"); /*for debug writing into a file*/
		u++;
	}
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
	// exit(0); /*for debug writing into a file*/
	return (0);
}

static t_v3	pixel_to_ray(t_app *a, int u, int v)
{
	t_v3	ray;

	ray = (t_v3){get_ratio(a, 'w', u), get_ratio(a, 'h', v), 1};

	/*
		now we should have a transformation matrix that translates this
		calculated ray to the camera position, then orients it.
	*/

	return (ray);
}

static t_v3	draw_ray(t_app *a, t_v3 ray)
{
	//given a ray, compute the color of the associated pixel?
	t_object	*closest;
	t_v3		poi;
	t_v3		col;

	closest = find_poi(a, ray, a->s.camera.position, &poi);
	if (closest)
		// col = (t_v3){0,1,0};
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

	int debug = 0;

	closest = NULL;
	closest_dist = FLT_MAX;
	current = a->s.objects_list;
	while (current)
	{
		dist = get_obj_poi(current->content, ray, origin, poi);
		if (dist < closest_dist)
		{
			debug += 1;
			closest_dist = dist;
			closest = current->content;
		}
		current = current->next;
	}
	// printf("%.2f ", closest_dist); /*for debug writing into a file*/
	return (closest);
}

static int	list_obj_type(t_list *obj)
{
	return (((t_object *)obj->content)->type);
}

static void	*list_obj_content(t_list *obj)
{
	(void)list_obj_content;
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
		get_pl_emmision,
		get_cy_emmision};

	if (obj->type < 0 || obj->type  >= MRT_NUM_OBJ_TYPES)
		return (get_emmision_passthrough(obj, poi));
	return (f[obj->type](obj, poi));
}





t_v3	get_pos_passthrough(t_object *me)
{
	(void)me;
	printf("can't get an position from this type of object\n");
	return ((t_v3){0, 0, 42});
}

t_v3	get_obj_pos(t_object *obj)
{
	t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *)  = {
		get_pos_passthrough,
		get_pos_passthrough,
		get_pos_passthrough,
		get_sp_position,
		get_pl_position,
		get_cy_position};

	if (obj->type < 0 || obj->type  >= MRT_NUM_OBJ_TYPES)
		return (get_pos_passthrough(obj));
	return (f[obj->type](obj));
}





float	get_poi_passthrough(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi)
{
	(void)me;
	(void)ray;
	(void)source;
	(void)poi;
	printf("can't get a poi from this type of object\n");
	return (FLT_MAX);
}

float	get_obj_poi(t_object *obj, t_v3 ray, t_v3 source, t_v3 *poi)
{
	float	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_v3, t_v3, t_v3 *)  = {
		get_poi_passthrough,
		get_poi_passthrough,
		get_poi_passthrough,
		get_sp_poi,
		get_pl_poi,
		get_cy_poi};

	if (obj->type < 0 || obj->type  >= MRT_NUM_OBJ_TYPES)
		return (get_poi_passthrough(obj, ray, source, poi));
	return (f[obj->type](obj, ray, source, poi));
}
