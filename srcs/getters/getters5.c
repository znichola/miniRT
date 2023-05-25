/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:05:12 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 12:06:58 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* get i-th light from scene */
t_light	*get_light(t_scene *s, int num)
{
	t_list	*current;
	int		i;

	current = s->lights_list;
	i = 0;
	while (current)
	{
		if (i == num)
			return (&((t_object *)(current->content))->object.l);
		current = current->next;
		i++;
	}
	return (NULL);
}

/* get object emmission (color) */
static t_v3	get_emmision_passthrough(t_object *me, t_intersection *i)
{
	(void)me;
	(void)i;
	printf("can't get an emmision from this type of object\n");
	return ((t_v3){42, 200, 42});
}

t_v3	get_obj_emmision(t_object *obj, t_intersection *i)
{
	static t_v3	(*f[MRT_NUM_OBJ_TYPES])(t_object *, t_intersection *) = {
		get_emmision_passthrough,
		get_emmision_passthrough,
		get_emmision_passthrough,
		get_sp_emmision,
		get_pl_emmision,
		get_cy_emmision,
		get_co_emmision};

	if (obj->type < 0 || obj->type >= MRT_NUM_OBJ_TYPES)
		return (get_emmision_passthrough(obj, i));
	return (f[obj->type](obj, i));
}
