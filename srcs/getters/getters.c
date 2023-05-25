/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:01:07 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 12:06:47 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* get object position */
static t_v3	get_pos_passthrough(t_object *me)
{
	(void)me;
	printf("can't get an position from this type of object\n");
	return ((t_v3){0, 0, 42});
}

static t_v3	get_cam_position(t_object *me)
{
	return (me->object.c.position);
}

static t_v3	get_light_pos(t_object *me)
{
	t_light	l;

	l = me->object.l;
	return (l.position);
}

t_v3	get_obj_pos(t_object *obj)
{
	static t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *) = {
		get_pos_passthrough,
		get_cam_position,
		get_light_pos,
		get_sp_position,
		get_pl_position,
		get_cy_position,
		get_co_position};

	if (obj->type < 0 || obj->type >= MRT_NUM_OBJ_TYPES)
		return (get_pos_passthrough(obj));
	return (f[obj->type](obj));
}
