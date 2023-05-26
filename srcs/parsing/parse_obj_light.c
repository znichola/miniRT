/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:59:00 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/26 12:48:08 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	consume_light(t_token **tokens, t_object *obj);
static int	validate_and_reformat_light(t_object *obj);

int	parse_light(t_token **tokens, t_object *obj)
{
	int	res;

	res = check_line_grammar(*tokens, e_light);
	if (res != 0)
		return (res);
	consume_light(tokens, obj);
	if (validate_and_reformat_light(obj) != 0)
		return (e_validation);
	return (0);
}

/* fill the object with the values from the tokens */
static void	consume_light(t_token **tokens, t_object *obj)
{
	obj->type = e_light;
	*tokens = (*tokens)->next;
	obj->object.l.position = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.l.ratio = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->object.l.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
}

/* check if values are valid */
static int	validate_and_reformat_light(t_object *obj)
{
	t_light	*l;

	l = &obj->object.l;
	if (l->ratio < 0 || l->ratio > 1)
		return (-1);
	if (validate_colour(&l->colour) != 0)
		return (-1);
	return (0);
}
