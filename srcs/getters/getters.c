/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:01:07 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/12 17:53:12 by skoulen          ###   ########.fr       */
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
			return (&((t_object *)(current->content))->object.l);
		}
		current = current->next;
		i++;
	}
	printf("GET_LIGHT CHAOS: num: %d\n", num);
	return (NULL);
}


/* get object emmission (color) */

static t_v3	get_emmision_passthrough(t_object *me, t_intersection *i)
{
	(void)me;
	(void)i;
	printf("can't get an emmision from this type of object\n");
	return ((t_v3){42,200,42});
}

t_v3	get_obj_emmision(t_object *obj, t_intersection *i)
{
	t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_intersection *)  = {
		get_emmision_passthrough,
		get_emmision_passthrough,
		get_emmision_passthrough,
		get_sp_emmision,
		get_pl_emmision,
		get_cy_emmision,
		get_co_emmision};

	if (obj->type < 0 || obj->type  >= MRT_NUM_OBJ_TYPES)
		return (get_emmision_passthrough(obj, i));
	return (f[obj->type](obj, i));
}


/* get object position */

static t_v3	get_pos_passthrough(t_object *me)
{
	(void)me;
	printf("can't get an position from this type of object\n");
	return ((t_v3){0, 0, 42});
}

static t_v3	get_light_pos(t_object *me)
{
	t_light	l;

	l = me->object.l;
	return (l.position);
}

t_v3	get_obj_pos(t_object *obj)
{
	t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *)  = {
		get_pos_passthrough,
		get_pos_passthrough,
		get_light_pos,
		get_sp_position,
		get_pl_position,
		get_cy_position,
		get_co_position};

	if (obj->type < 0 || obj->type  >= MRT_NUM_OBJ_TYPES)
		return (get_pos_passthrough(obj));
	return (f[obj->type](obj));
}


/* point of intersection with object */

static float	get_poi_passthrough(t_object *me, t_v3 ray, t_v3 source, t_intersection *i)
{
	(void)me;
	(void)ray;
	(void)source;
	(void)i;
	printf("can't get a poi from this type of object\n");
	return (FLT_MAX);
}

float	get_obj_poi(t_object *obj, t_v3 ray, t_v3 source, t_intersection *i)
{
	float	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_v3, t_v3, t_intersection *) = {
		get_poi_passthrough,
		get_poi_passthrough,
		get_poi_passthrough,
		get_sp_poi,
		get_pl_poi,
		get_cy_poi,
		get_co_poi};

	if (obj->type < 0 || obj->type  >= MRT_NUM_OBJ_TYPES)
		return (get_poi_passthrough(obj, ray, source, i));
	return (f[obj->type](obj, ray, source, i));
}

/* get normal unitvec of surface at point of intersection */

static t_v3	get_poi_norm_passthrough(t_object *obj, t_intersection *i)
{
	(void)obj;
	(void)i;
	printf("can't get normal vector of surface for this type of object\n");
	return ((t_v3){42,42,42});
}

t_v3	get_poi_norm(t_object* obj, t_intersection *i)
{
	t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_intersection *) = {
		get_poi_norm_passthrough,
		get_poi_norm_passthrough,
		get_poi_norm_passthrough,
		get_sp_poi_norm,
		get_pl_poi_norm,
		get_cy_poi_norm,
		get_co_poi_norm
	};

	if (obj->type < 0 || obj->type >= MRT_NUM_OBJ_TYPES)
		return (get_poi_norm_passthrough(obj, i));
	return (f[obj->type](obj, i));
}
