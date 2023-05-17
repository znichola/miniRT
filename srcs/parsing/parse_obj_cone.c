/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:38:37 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/17 15:46:14 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_cone(t_token *tokens);
static void	consume_cone(t_token **tokens, t_object *obj);
static int	validate_and_reformat_cone(t_object *obj);
static void consume_optional_cone(t_token **tokens, t_cone *co);

int	parse_cone(t_token **tokens, t_object *obj)
{
	int	res;

	printf("cone\n");
	res = check_grammar_cone(*tokens);
	if (res != 0)
		return (res);
	consume_cone(tokens, obj);
	if (validate_and_reformat_cone(obj) != 0)
		return (e_validation);
	return (0);
}

/* check if grammar for cone is valid */
static int	check_grammar_cone(t_token *tokens)
{
	return (check_line_grammar(tokens));
}

/* fill the object with the values from the tokens */
static void	consume_cone(t_token **tokens, t_object *obj)
{
	obj->type = e_cone;
	*tokens = (*tokens)->next; //skip the identifier
	obj->object.co.position = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.co.orientation = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.co.radius = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->object.co.height = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->object.co.angle = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->object.co.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;

	consume_optional_cone(tokens, &obj->object.co);

	*tokens = (*tokens)->next; //skip the end-of-line token
}

static void consume_optional_cone(t_token **tokens, t_cone *co)
{
	co->texture.filepath = NULL;
	co->bump.filepath = NULL;
	co->normal.filepath = NULL;
	co->checker = 0;
	while (*tokens && (*tokens)->type == e_optional)
	{
		if ((*tokens)->value.opt.type == e_texture)
			co->texture.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_bump)
			co->bump.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_normal)
			co->normal.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_checker)
			co->checker = ft_strcmp((*tokens)->value.opt.filepath, "true") == 0;
		*tokens = (*tokens)->next;
	}
}

/* check if values are valid */
static int	validate_and_reformat_cone(t_object *obj)
{
	t_cone	*co;

	co = &obj->object.co;
	if (validate_orientation(&co->orientation) != 0)
		return (-1);
	if (co->radius < 0)
		return (-1);
	co->radius /= 2;
	if (co->height < 0)
		return (-1);
	if (validate_colour(&co->colour) != 0)
		return (-1);
	return (0);
}
