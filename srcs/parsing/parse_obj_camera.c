/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:58:49 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/11 12:20:18 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_camera(t_token *tokens);
static void	consume_camera(t_token **tokens, t_object *obj);
static int	validate_and_reformat_camera(t_object *obj);

int	parse_camera(t_token **tokens, t_object *obj)
{
	int	res;

	printf("CAMERA\n");
	res = check_grammar_camera(*tokens);
	if (res != 0)
		return (res);
	consume_camera(tokens, obj);
	if (validate_and_reformat_camera(obj) != 0)
		return (e_validation);
	return (0);
}

/* check if grammar for camera is valid */
static int	check_grammar_camera(t_token *tokens)
{
	return (check_line_grammar(tokens));
}

/* fill the object with the values from the tokens */
static void	consume_camera(t_token **tokens, t_object *obj)
{
	obj->type = e_camera;
	*tokens = (*tokens)->next; //skip the identifier
	obj->object.c.position = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.c.orientation = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.c.fov = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;

	*tokens = (*tokens)->next; //skip the end-of-line token
}

/* check if values are valid */
static int	validate_and_reformat_camera(t_object *obj)
{
	t_camera	*c;

	c = &obj->object.c;
	if (validate_orientation(&c->orientation) != 0)
		return (-1);
	if (c->fov <= 0 || c->fov > 180)
		return (-1);
	return (0);
}
