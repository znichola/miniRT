/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:58:49 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/29 14:01:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	consume_camera(t_token **tokens, t_object *obj);
static int	validate_and_reformat_camera(t_object *obj);

int	parse_camera(t_token **tokens, t_object *obj)
{
	int	res;

	res = check_line_grammar(*tokens, e_camera);
	if (res != 0)
		return (res);
	consume_camera(tokens, obj);
	res = validate_and_reformat_camera(obj);
	return (res);
}

/* fill the object with the values from the tokens */
static void	consume_camera(t_token **tokens, t_object *obj)
{
	obj->type = e_camera;
	*tokens = (*tokens)->next;
	obj->object.c.position = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.c.orientation = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.c.fov = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
}

/* check if values are valid */
static int	validate_and_reformat_camera(t_object *obj)
{
	t_camera	*c;

	c = &obj->object.c;
	if (validate_orientation(&c->orientation) != 0)
		return (e_invalid_orientation);
	if (c->fov <= 0 || c->fov > 180)
		return (e_invalid_fov);
	c->fov = c->fov * M_PI_2 / 180.0f;
	calculate_viewport(c);
	return (0);
}
