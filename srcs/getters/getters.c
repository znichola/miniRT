/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:01:07 by skoulen           #+#    #+#             */
/*   Updated: 2023/04/25 15:25:49 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* get i-th light from scene */
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


/* get object emmission (color) */

static t_v3	get_emmision_passthrough(t_object *me, t_v3 poi)
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


/* get object position */

static t_v3	get_pos_passthrough(t_object *me)
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


/* point of intersection with object */

static float	get_poi_passthrough(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi)
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

/* get normal unitvec of surface at point of intersection */
t_v3	get_poi_norm(t_object* obj, t_v3 point)
{
	if (obj->type == e_sphere)
	{
		return (v3_unitvec(v3_subtract(point, obj->object.sp.position)));
	}
	else if (obj->type == e_plane)
	{
		return (v3_unitvec(obj->object.pl.orientation));
	}
}
