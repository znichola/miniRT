/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:53:52 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 12:04:51 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* point of intersection with object */
static float	get_poi_passthrough(t_object *me, t_v3 ray, t_v3 source,
	t_intersection *i)
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
	static float	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_v3, t_v3,
			t_intersection *) = {
		get_poi_passthrough,
		get_poi_passthrough,
		get_poi_passthrough,
		get_sp_poi,
		get_pl_poi,
		get_cy_poi,
		get_co_poi};

	if (obj->type < 0 || obj->type >= MRT_NUM_OBJ_TYPES)
		return (get_poi_passthrough(obj, ray, source, i));
	return (f[obj->type](obj, ray, source, i));
}

/* get normal unitvec of surface at point of intersection */
static t_v3	get_poi_norm_passthrough(t_object *obj, t_intersection *i)
{
	(void)obj;
	(void)i;
	printf("can't get normal vector of surface for this type of object\n");
	return ((t_v3){42, 42, 42});
}

/*
	this includes the displacment from the bump map!
*/
t_v3	get_poi_norm(t_object *obj, t_intersection *i)
{
	static t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_intersection *) = {
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
	if (get_obj_bmp(obj)->img != NULL)
		return (get_bmp_adjusted_normal(obj, i));
	return (f[obj->type](obj, i));
}

float	*ref_obj_p3(t_object *o)
{
	if (o->type == e_cone)
		return (&o->object.co.angle);
	return (NULL);
}
